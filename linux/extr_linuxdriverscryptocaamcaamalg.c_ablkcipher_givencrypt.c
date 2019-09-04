#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ablkcipher_request {int dummy; } ;
struct skcipher_givcrypt_request {struct ablkcipher_request creq; } ;
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct caam_ctx {int /*<<< orphan*/  sh_desc_givenc_dma; int /*<<< orphan*/  sh_desc_givenc; struct device* jrdev; } ;
struct ablkcipher_edesc {int /*<<< orphan*/ * hw_desc; } ;

/* Variables and functions */
 int CAAM_CMD_SZ ; 
 int DESC_JOB_IO_LEN ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct ablkcipher_edesc*) ; 
 int PTR_ERR (struct ablkcipher_edesc*) ; 
 int /*<<< orphan*/  ablkcipher_encrypt_done ; 
 struct ablkcipher_edesc* ablkcipher_giv_edesc_alloc (struct skcipher_givcrypt_request*,int) ; 
 int /*<<< orphan*/  ablkcipher_unmap (struct device*,struct ablkcipher_edesc*,struct ablkcipher_request*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ablkcipher_request*) ; 
 struct caam_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  init_ablkcipher_giv_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ablkcipher_edesc*,struct ablkcipher_request*) ; 
 int /*<<< orphan*/  kfree (struct ablkcipher_edesc*) ; 

__attribute__((used)) static int ablkcipher_givencrypt(struct skcipher_givcrypt_request *creq)
{
	struct ablkcipher_request *req = &creq->creq;
	struct ablkcipher_edesc *edesc;
	struct crypto_ablkcipher *ablkcipher = crypto_ablkcipher_reqtfm(req);
	struct caam_ctx *ctx = crypto_ablkcipher_ctx(ablkcipher);
	struct device *jrdev = ctx->jrdev;
	u32 *desc;
	int ret = 0;

	/* allocate extended descriptor */
	edesc = ablkcipher_giv_edesc_alloc(creq, DESC_JOB_IO_LEN * CAAM_CMD_SZ);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	/* Create and submit job descriptor*/
	init_ablkcipher_giv_job(ctx->sh_desc_givenc, ctx->sh_desc_givenc_dma,
				edesc, req);
#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "ablkcipher jobdesc@" __stringify(__LINE__) ": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, edesc->hw_desc,
		       desc_bytes(edesc->hw_desc), 1);
#endif
	desc = edesc->hw_desc;
	ret = caam_jr_enqueue(jrdev, desc, ablkcipher_encrypt_done, req);

	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		ablkcipher_unmap(jrdev, edesc, req);
		kfree(edesc);
	}

	return ret;
}