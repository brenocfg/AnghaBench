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
struct pci_dev {int dummy; } ;
struct cxl_context {int kernelapi; } ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cxl_context* ERR_CAST (struct cxl_afu*) ; 
 struct cxl_context* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct cxl_afu*) ; 
 struct cxl_context* cxl_context_alloc () ; 
 int cxl_context_init (struct cxl_context*,struct cxl_afu*,int) ; 
 struct cxl_afu* cxl_pci_to_afu (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct cxl_context*) ; 

struct cxl_context *cxl_dev_context_init(struct pci_dev *dev)
{
	struct cxl_afu *afu;
	struct cxl_context  *ctx;
	int rc;

	afu = cxl_pci_to_afu(dev);
	if (IS_ERR(afu))
		return ERR_CAST(afu);

	ctx = cxl_context_alloc();
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	ctx->kernelapi = true;

	/* Make it a slave context.  We can promote it later? */
	rc = cxl_context_init(ctx, afu, false);
	if (rc)
		goto err_ctx;

	return ctx;

err_ctx:
	kfree(ctx);
	return ERR_PTR(rc);
}