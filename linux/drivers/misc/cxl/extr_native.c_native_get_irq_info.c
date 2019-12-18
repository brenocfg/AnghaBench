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
struct cxl_irq_info {scalar_t__ proc_handle; void* errstat; void* afu_err; void* dsr; void* dar; void* dsisr; } ;
struct cxl_afu {int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (int /*<<< orphan*/ ,struct cxl_afu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_ERR_An ; 
 int /*<<< orphan*/  CXL_PSL_DAR_An ; 
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int /*<<< orphan*/  CXL_PSL_DSR_An ; 
 int /*<<< orphan*/  CXL_PSL_ErrStat_An ; 
 int EIO ; 
 scalar_t__ cxl_is_power8 () ; 
 TYPE_1__* cxl_ops ; 
 void* cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct cxl_afu*) ; 

__attribute__((used)) static int native_get_irq_info(struct cxl_afu *afu, struct cxl_irq_info *info)
{
	/* If the adapter has gone away, we can't get any meaningful
	 * information.
	 */
	if (!cxl_ops->link_ok(afu->adapter, afu))
		return -EIO;

	info->dsisr = cxl_p2n_read(afu, CXL_PSL_DSISR_An);
	info->dar = cxl_p2n_read(afu, CXL_PSL_DAR_An);
	if (cxl_is_power8())
		info->dsr = cxl_p2n_read(afu, CXL_PSL_DSR_An);
	info->afu_err = cxl_p2n_read(afu, CXL_AFU_ERR_An);
	info->errstat = cxl_p2n_read(afu, CXL_PSL_ErrStat_An);
	info->proc_handle = 0;

	return 0;
}