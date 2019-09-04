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
typedef  int u64 ;
struct cxl_afu {int serr_hwirq; int /*<<< orphan*/ * err_irq_name; int /*<<< orphan*/  serr_virq; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_SERR_An ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cxl_is_power8 () ; 
 scalar_t__ cxl_is_power9 () ; 
 int cxl_p1n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int cxl_register_one_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cxl_afu*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  native_slice_irq_err ; 

int cxl_native_register_serr_irq(struct cxl_afu *afu)
{
	u64 serr;
	int rc;

	afu->err_irq_name = kasprintf(GFP_KERNEL, "cxl-%s-err",
				      dev_name(&afu->dev));
	if (!afu->err_irq_name)
		return -ENOMEM;

	if ((rc = cxl_register_one_irq(afu->adapter, native_slice_irq_err, afu,
				       &afu->serr_hwirq,
				       &afu->serr_virq, afu->err_irq_name))) {
		kfree(afu->err_irq_name);
		afu->err_irq_name = NULL;
		return rc;
	}

	serr = cxl_p1n_read(afu, CXL_PSL_SERR_An);
	if (cxl_is_power8())
		serr = (serr & 0x00ffffffffff0000ULL) | (afu->serr_hwirq & 0xffff);
	if (cxl_is_power9()) {
		/*
		 * By default, all errors are masked. So don't set all masks.
		 * Slice errors will be transfered.
		 */
		serr = (serr & ~0xff0000007fffffffULL) | (afu->serr_hwirq & 0xffff);
	}
	cxl_p1n_write(afu, CXL_PSL_SERR_An, serr);

	return 0;
}