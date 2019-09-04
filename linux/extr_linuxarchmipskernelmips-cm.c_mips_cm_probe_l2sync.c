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
typedef  int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CM_GCR_L2_ONLY_SYNC_BASE_SYNCBASE ; 
 int CM_GCR_L2_ONLY_SYNC_BASE_SYNCEN ; 
 unsigned int CM_GCR_REV_MAJOR ; 
 int /*<<< orphan*/  MIPS_CM_L2SYNC_SIZE ; 
 unsigned int __ffs (unsigned int) ; 
 int /*<<< orphan*/  ioremap_nocache (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_cm_l2sync_base ; 
 int mips_cm_l2sync_phys_base () ; 
 unsigned int read_gcr_rev () ; 
 int /*<<< orphan*/  write_gcr_l2_only_sync_base (int) ; 

__attribute__((used)) static void mips_cm_probe_l2sync(void)
{
	unsigned major_rev;
	phys_addr_t addr;

	/* L2-only sync was introduced with CM major revision 6 */
	major_rev = (read_gcr_rev() & CM_GCR_REV_MAJOR) >>
		__ffs(CM_GCR_REV_MAJOR);
	if (major_rev < 6)
		return;

	/* Find a location for the L2 sync region */
	addr = mips_cm_l2sync_phys_base();
	BUG_ON((addr & CM_GCR_L2_ONLY_SYNC_BASE_SYNCBASE) != addr);
	if (!addr)
		return;

	/* Set the region base address & enable it */
	write_gcr_l2_only_sync_base(addr | CM_GCR_L2_ONLY_SYNC_BASE_SYNCEN);

	/* Map the region */
	mips_cm_l2sync_base = ioremap_nocache(addr, MIPS_CM_L2SYNC_SIZE);
}