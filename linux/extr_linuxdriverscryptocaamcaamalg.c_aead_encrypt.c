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
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct caam_ctx {struct device* jrdev; } ;
struct aead_request {int dummy; } ;
struct aead_edesc {int /*<<< orphan*/ * hw_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENC_DESC_JOB_IO_LEN ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct aead_edesc*) ; 
 int PTR_ERR (struct aead_edesc*) ; 
 struct aead_edesc* aead_edesc_alloc (struct aead_request*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  aead_encrypt_done ; 
 int /*<<< orphan*/  aead_unmap (struct device*,struct aead_edesc*,struct aead_request*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aead_request*) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  init_authenc_job (struct aead_request*,struct aead_edesc*,int,int) ; 
 int /*<<< orphan*/  kfree (struct aead_edesc*) ; 

__attribute__((used)) static int aead_encrypt(struct aead_request *req)
{
	struct aead_edesc *edesc;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	bool all_contig;
	u32 *desc;
	int ret = 0;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, AUTHENC_DESC_JOB_IO_LEN,
				 &all_contig, true);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	/* Create and submit job descriptor */
	init_authenc_job(req, edesc, all_contig, true);
#ifdef DEBUG
	print_hex_dump(KERN_ERR, "aead jobdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, edesc->hw_desc,
		       desc_bytes(edesc->hw_desc), 1);
#endif

	desc = edesc->hw_desc;
	ret = caam_jr_enqueue(jrdev, desc, aead_encrypt_done, req);
	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		aead_unmap(jrdev, edesc, req);
		kfree(edesc);
	}

	return ret;
}