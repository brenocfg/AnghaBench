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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_rdev; } ;
struct file {struct cxl_context* private_data; } ;
struct cxl_context {int /*<<< orphan*/  pe; } ;
struct cxl_afu {int /*<<< orphan*/  current_mode; } ;
struct cxl {int slices; int /*<<< orphan*/  dev; int /*<<< orphan*/  afu_list_lock; struct cxl_afu** afu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (struct cxl*,struct cxl_afu*) ;} ;

/* Variables and functions */
 int CXL_DEVT_ADAPTER (int /*<<< orphan*/ ) ; 
 int CXL_DEVT_AFU (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cxl_afu_get (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_afu_put (struct cxl_afu*) ; 
 struct cxl_context* cxl_context_alloc () ; 
 int cxl_context_init (struct cxl_context*,struct cxl_afu*,int) ; 
 int /*<<< orphan*/  cxl_context_set_mapping (struct cxl_context*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cxl_ops ; 
 struct cxl* get_cxl_adapter (int) ; 
 int /*<<< orphan*/  pr_devel (char*,int,...) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxl*,struct cxl_afu*) ; 

__attribute__((used)) static int __afu_open(struct inode *inode, struct file *file, bool master)
{
	struct cxl *adapter;
	struct cxl_afu *afu;
	struct cxl_context *ctx;
	int adapter_num = CXL_DEVT_ADAPTER(inode->i_rdev);
	int slice = CXL_DEVT_AFU(inode->i_rdev);
	int rc = -ENODEV;

	pr_devel("afu_open afu%i.%i\n", slice, adapter_num);

	if (!(adapter = get_cxl_adapter(adapter_num)))
		return -ENODEV;

	if (slice > adapter->slices)
		goto err_put_adapter;

	spin_lock(&adapter->afu_list_lock);
	if (!(afu = adapter->afu[slice])) {
		spin_unlock(&adapter->afu_list_lock);
		goto err_put_adapter;
	}

	/*
	 * taking a ref to the afu so that it doesn't go away
	 * for rest of the function. This ref is released before
	 * we return.
	 */
	cxl_afu_get(afu);
	spin_unlock(&adapter->afu_list_lock);

	if (!afu->current_mode)
		goto err_put_afu;

	if (!cxl_ops->link_ok(adapter, afu)) {
		rc = -EIO;
		goto err_put_afu;
	}

	if (!(ctx = cxl_context_alloc())) {
		rc = -ENOMEM;
		goto err_put_afu;
	}

	rc = cxl_context_init(ctx, afu, master);
	if (rc)
		goto err_put_afu;

	cxl_context_set_mapping(ctx, inode->i_mapping);

	pr_devel("afu_open pe: %i\n", ctx->pe);
	file->private_data = ctx;

	/* indicate success */
	rc = 0;

err_put_afu:
	/* release the ref taken earlier */
	cxl_afu_put(afu);
err_put_adapter:
	put_device(&adapter->dev);
	return rc;
}