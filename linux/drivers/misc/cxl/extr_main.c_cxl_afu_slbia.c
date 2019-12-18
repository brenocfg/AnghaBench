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
struct cxl_afu {int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (int /*<<< orphan*/ ,struct cxl_afu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_SLBIA_An ; 
 unsigned long CXL_TIMEOUT ; 
 int /*<<< orphan*/  CXL_TLB_SLB_IQ_ALL ; 
 int CXL_TLB_SLB_P ; 
 int EBUSY ; 
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* cxl_ops ; 
 int cxl_p2n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct cxl_afu*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int cxl_afu_slbia(struct cxl_afu *afu)
{
	unsigned long timeout = jiffies + (HZ * CXL_TIMEOUT);

	pr_devel("cxl_afu_slbia issuing SLBIA command\n");
	cxl_p2n_write(afu, CXL_SLBIA_An, CXL_TLB_SLB_IQ_ALL);
	while (cxl_p2n_read(afu, CXL_SLBIA_An) & CXL_TLB_SLB_P) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&afu->dev, "WARNING: CXL AFU SLBIA timed out!\n");
			return -EBUSY;
		}
		/* If the adapter has gone down, we can assume that we
		 * will PERST it and that will invalidate everything.
		 */
		if (!cxl_ops->link_ok(afu->adapter, afu))
			return -EIO;
		cpu_relax();
	}
	return 0;
}