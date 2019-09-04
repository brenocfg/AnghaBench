#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_request {scalar_t__ iv; int /*<<< orphan*/  cryptlen; struct scatterlist* dst; struct scatterlist* src; } ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_type; } ;
struct cipher_req_ctx {int /*<<< orphan*/  iv; int /*<<< orphan*/  backup_info; TYPE_1__ gen_ctx; } ;
struct cc_cipher_ctx {int cipher_mode; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int ALIGN (int /*<<< orphan*/ ,unsigned int) ; 
#define  DRV_CIPHER_CBC 129 
#define  DRV_CIPHER_CTR 128 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int /*<<< orphan*/  cc_unmap_cipher_request (struct device*,struct cipher_req_ctx*,unsigned int,struct scatterlist*,struct scatterlist*) ; 
 int /*<<< orphan*/  cc_update_ctr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,struct scatterlist*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_complete (struct skcipher_request*,int) ; 
 struct cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void cc_cipher_complete(struct device *dev, void *cc_req, int err)
{
	struct skcipher_request *req = (struct skcipher_request *)cc_req;
	struct scatterlist *dst = req->dst;
	struct scatterlist *src = req->src;
	struct cipher_req_ctx *req_ctx = skcipher_request_ctx(req);
	struct crypto_skcipher *sk_tfm = crypto_skcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_skcipher_tfm(sk_tfm);
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	unsigned int ivsize = crypto_skcipher_ivsize(sk_tfm);
	unsigned int len;

	cc_unmap_cipher_request(dev, req_ctx, ivsize, src, dst);

	switch (ctx_p->cipher_mode) {
	case DRV_CIPHER_CBC:
		/*
		 * The crypto API expects us to set the req->iv to the last
		 * ciphertext block. For encrypt, simply copy from the result.
		 * For decrypt, we must copy from a saved buffer since this
		 * could be an in-place decryption operation and the src is
		 * lost by this point.
		 */
		if (req_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT)  {
			memcpy(req->iv, req_ctx->backup_info, ivsize);
			kzfree(req_ctx->backup_info);
		} else if (!err) {
			len = req->cryptlen - ivsize;
			scatterwalk_map_and_copy(req->iv, req->dst, len,
						 ivsize, 0);
		}
		break;

	case DRV_CIPHER_CTR:
		/* Compute the counter of the last block */
		len = ALIGN(req->cryptlen, AES_BLOCK_SIZE) / AES_BLOCK_SIZE;
		cc_update_ctr((u8 *)req->iv, len);
		break;

	default:
		break;
	}

	kzfree(req_ctx->iv);

	skcipher_request_complete(req, err);
}