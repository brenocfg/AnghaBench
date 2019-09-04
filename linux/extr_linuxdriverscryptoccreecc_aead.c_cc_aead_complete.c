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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_aead_ctx {scalar_t__ cipher_mode; scalar_t__ authsize; } ;
struct aead_request {scalar_t__ cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  iv; } ;
struct TYPE_2__ {scalar_t__ op_type; } ;
struct aead_req_ctx {scalar_t__ ctr_iv; scalar_t__ backup_giv; int /*<<< orphan*/  dst_sgl; int /*<<< orphan*/  mac_buf; scalar_t__ dst_offset; scalar_t__ is_icv_fragmented; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  icv_virt_addr; TYPE_1__ gen_ctx; int /*<<< orphan*/  backup_iv; } ;

/* Variables and functions */
 scalar_t__ CCM_BLOCK_IV_OFFSET ; 
 int /*<<< orphan*/  CCM_BLOCK_IV_SIZE ; 
 int /*<<< orphan*/  CC_SG_FROM_BUF ; 
 int /*<<< orphan*/  CTR_RFC3686_IV_SIZE ; 
 scalar_t__ CTR_RFC3686_NONCE_SIZE ; 
 scalar_t__ DRV_CIPHER_CCM ; 
 scalar_t__ DRV_CIPHER_CTR ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int EBADMSG ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_copy_sg_portion (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_unmap_aead_request (struct device*,struct aead_request*) ; 
 int /*<<< orphan*/  cc_zero_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (void*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_aead_complete(struct device *dev, void *cc_req, int err)
{
	struct aead_request *areq = (struct aead_request *)cc_req;
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	struct crypto_aead *tfm = crypto_aead_reqtfm(cc_req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);

	cc_unmap_aead_request(dev, areq);

	/* Restore ordinary iv pointer */
	areq->iv = areq_ctx->backup_iv;

	if (err)
		goto done;

	if (areq_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT) {
		if (memcmp(areq_ctx->mac_buf, areq_ctx->icv_virt_addr,
			   ctx->authsize) != 0) {
			dev_dbg(dev, "Payload authentication failure, (auth-size=%d, cipher=%d)\n",
				ctx->authsize, ctx->cipher_mode);
			/* In case of payload authentication failure, MUST NOT
			 * revealed the decrypted message --> zero its memory.
			 */
			cc_zero_sgl(areq->dst, areq_ctx->cryptlen);
			err = -EBADMSG;
		}
	} else { /*ENCRYPT*/
		if (areq_ctx->is_icv_fragmented) {
			u32 skip = areq->cryptlen + areq_ctx->dst_offset;

			cc_copy_sg_portion(dev, areq_ctx->mac_buf,
					   areq_ctx->dst_sgl, skip,
					   (skip + ctx->authsize),
					   CC_SG_FROM_BUF);
		}

		/* If an IV was generated, copy it back to the user provided
		 * buffer.
		 */
		if (areq_ctx->backup_giv) {
			if (ctx->cipher_mode == DRV_CIPHER_CTR)
				memcpy(areq_ctx->backup_giv, areq_ctx->ctr_iv +
				       CTR_RFC3686_NONCE_SIZE,
				       CTR_RFC3686_IV_SIZE);
			else if (ctx->cipher_mode == DRV_CIPHER_CCM)
				memcpy(areq_ctx->backup_giv, areq_ctx->ctr_iv +
				       CCM_BLOCK_IV_OFFSET, CCM_BLOCK_IV_SIZE);
		}
	}
done:
	aead_request_complete(areq, err);
}