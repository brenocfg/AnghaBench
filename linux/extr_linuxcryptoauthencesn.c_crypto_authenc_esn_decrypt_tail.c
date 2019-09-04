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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct crypto_authenc_esn_ctx {int /*<<< orphan*/  enc; struct crypto_ahash* auth; scalar_t__ reqoff; } ;
struct crypto_ahash {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct authenc_esn_request_ctx {int /*<<< orphan*/  dst; scalar_t__ tail; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; } ;
struct aead_request {unsigned int cryptlen; unsigned int assoclen; int /*<<< orphan*/  iv; TYPE_1__ base; struct scatterlist* dst; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 struct authenc_esn_request_ctx* aead_request_ctx (struct aead_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_esn_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_ahash_alignmask (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 struct scatterlist* scatterwalk_ffwd (int /*<<< orphan*/ ,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,int,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_authenc_esn_decrypt_tail(struct aead_request *req,
					   unsigned int flags)
{
	struct crypto_aead *authenc_esn = crypto_aead_reqtfm(req);
	unsigned int authsize = crypto_aead_authsize(authenc_esn);
	struct authenc_esn_request_ctx *areq_ctx = aead_request_ctx(req);
	struct crypto_authenc_esn_ctx *ctx = crypto_aead_ctx(authenc_esn);
	struct skcipher_request *skreq = (void *)(areq_ctx->tail +
						  ctx->reqoff);
	struct crypto_ahash *auth = ctx->auth;
	u8 *ohash = PTR_ALIGN((u8 *)areq_ctx->tail,
			      crypto_ahash_alignmask(auth) + 1);
	unsigned int cryptlen = req->cryptlen - authsize;
	unsigned int assoclen = req->assoclen;
	struct scatterlist *dst = req->dst;
	u8 *ihash = ohash + crypto_ahash_digestsize(auth);
	u32 tmp[2];

	if (!authsize)
		goto decrypt;

	/* Move high-order bits of sequence number back. */
	scatterwalk_map_and_copy(tmp, dst, 4, 4, 0);
	scatterwalk_map_and_copy(tmp + 1, dst, assoclen + cryptlen, 4, 0);
	scatterwalk_map_and_copy(tmp, dst, 0, 8, 1);

	if (crypto_memneq(ihash, ohash, authsize))
		return -EBADMSG;

decrypt:

	sg_init_table(areq_ctx->dst, 2);
	dst = scatterwalk_ffwd(areq_ctx->dst, dst, assoclen);

	skcipher_request_set_tfm(skreq, ctx->enc);
	skcipher_request_set_callback(skreq, flags,
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(skreq, dst, dst, cryptlen, req->iv);

	return crypto_skcipher_decrypt(skreq);
}