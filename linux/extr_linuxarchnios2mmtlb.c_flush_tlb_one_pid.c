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
struct TYPE_2__ {unsigned int tlb_num_ways; unsigned int tlb_num_lines; } ;

/* Variables and functions */
 unsigned int CONFIG_NIOS2_IO_REGION_BASE ; 
 int /*<<< orphan*/  CTL_PTEADDR ; 
 int /*<<< orphan*/  CTL_TLBACC ; 
 int /*<<< orphan*/  CTL_TLBMISC ; 
 unsigned long MAX_PHYS_ADDR ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 unsigned long RDCTL (int /*<<< orphan*/ ) ; 
 unsigned long TLBMISC_PID_MASK ; 
 unsigned long TLBMISC_PID_SHIFT ; 
 unsigned long TLBMISC_RD ; 
 unsigned int TLBMISC_WAY_SHIFT ; 
 unsigned long TLBMISC_WE ; 
 unsigned long TLB_INDEX_MASK ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  get_misc_and_pid (unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,...) ; 

void flush_tlb_one_pid(unsigned long addr, unsigned long mmu_pid)
{
	unsigned int way;
	unsigned long org_misc, pid_misc;

	pr_debug("Flush tlb-entry for vaddr=%#lx\n", addr);

	/* remember pid/way until we return. */
	get_misc_and_pid(&org_misc, &pid_misc);

	WRCTL(CTL_PTEADDR, (addr >> PAGE_SHIFT) << 2);

	for (way = 0; way < cpuinfo.tlb_num_ways; way++) {
		unsigned long pteaddr;
		unsigned long tlbmisc;
		unsigned long pid;

		tlbmisc = pid_misc | TLBMISC_RD | (way << TLBMISC_WAY_SHIFT);
		WRCTL(CTL_TLBMISC, tlbmisc);
		pteaddr = RDCTL(CTL_PTEADDR);
		tlbmisc = RDCTL(CTL_TLBMISC);
		pid = (tlbmisc >> TLBMISC_PID_SHIFT) & TLBMISC_PID_MASK;
		if (((((pteaddr >> 2) & 0xfffff)) == (addr >> PAGE_SHIFT)) &&
				pid == mmu_pid) {
			unsigned long vaddr = CONFIG_NIOS2_IO_REGION_BASE +
				((PAGE_SIZE * cpuinfo.tlb_num_lines) * way) +
				(addr & TLB_INDEX_MASK);
			pr_debug("Flush entry by writing %#lx way=%dl pid=%ld\n",
				vaddr, way, (pid_misc >> TLBMISC_PID_SHIFT));

			WRCTL(CTL_PTEADDR, (vaddr >> 12) << 2);
			tlbmisc = pid_misc | TLBMISC_WE |
				(way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			WRCTL(CTL_TLBACC, (MAX_PHYS_ADDR >> PAGE_SHIFT));
		}
	}

	WRCTL(CTL_TLBMISC, org_misc);
}