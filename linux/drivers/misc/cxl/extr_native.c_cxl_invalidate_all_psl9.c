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
typedef  int /*<<< orphan*/  u64 ;
struct cxl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_ok ) (struct cxl*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned long CXL_TIMEOUT ; 
 int /*<<< orphan*/  CXL_XSL9_IERAT ; 
 int /*<<< orphan*/  CXL_XSL9_IERAT_IALL ; 
 int CXL_XSL9_IERAT_IINPROG ; 
 int /*<<< orphan*/  CXL_XSL9_IERAT_INVR ; 
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
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  stub1 (struct cxl*,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int cxl_invalidate_all_psl9(struct cxl *adapter)
{
	unsigned long timeout = jiffies + (HZ * CXL_TIMEOUT);
	u64 ierat;

	pr_devel("CXL adapter - invalidation of all ERAT entries\n");

	/* Invalidates all ERAT entries for Radix or HPT */
	ierat = CXL_XSL9_IERAT_IALL;
	if (radix_enabled())
		ierat |= CXL_XSL9_IERAT_INVR;
	cxl_p1_write(adapter, CXL_XSL9_IERAT, ierat);

	while (cxl_p1_read(adapter, CXL_XSL9_IERAT) & CXL_XSL9_IERAT_IINPROG) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&adapter->dev,
			"WARNING: CXL adapter invalidation of all ERAT entries timed out!\n");
			return -EBUSY;
		}
		if (!cxl_ops->link_ok(adapter, NULL))
			return -EIO;
		cpu_relax();
	}
	return 0;
}