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
struct cxl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (struct cxl*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_AFUSEL ; 
 int /*<<< orphan*/  CXL_PSL_AFUSEL_A ; 
 int /*<<< orphan*/  CXL_PSL_SLBIA ; 
 int /*<<< orphan*/  CXL_PSL_TLBIA ; 
 unsigned long CXL_TIMEOUT ; 
 int /*<<< orphan*/  CXL_TLB_SLB_IQ_ALL ; 
 int CXL_TLB_SLB_P ; 
 int EBUSY ; 
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* cxl_ops ; 
 int cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 int /*<<< orphan*/  stub1 (struct cxl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct cxl*,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int cxl_invalidate_all_psl8(struct cxl *adapter)
{
	unsigned long timeout = jiffies + (HZ * CXL_TIMEOUT);

	pr_devel("CXL adapter wide TLBIA & SLBIA\n");

	cxl_p1_write(adapter, CXL_PSL_AFUSEL, CXL_PSL_AFUSEL_A);

	cxl_p1_write(adapter, CXL_PSL_TLBIA, CXL_TLB_SLB_IQ_ALL);
	while (cxl_p1_read(adapter, CXL_PSL_TLBIA) & CXL_TLB_SLB_P) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&adapter->dev, "WARNING: CXL adapter wide TLBIA timed out!\n");
			return -EBUSY;
		}
		if (!cxl_ops->link_ok(adapter, NULL))
			return -EIO;
		cpu_relax();
	}

	cxl_p1_write(adapter, CXL_PSL_SLBIA, CXL_TLB_SLB_IQ_ALL);
	while (cxl_p1_read(adapter, CXL_PSL_SLBIA) & CXL_TLB_SLB_P) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&adapter->dev, "WARNING: CXL adapter wide SLBIA timed out!\n");
			return -EBUSY;
		}
		if (!cxl_ops->link_ok(adapter, NULL))
			return -EIO;
		cpu_relax();
	}
	return 0;
}