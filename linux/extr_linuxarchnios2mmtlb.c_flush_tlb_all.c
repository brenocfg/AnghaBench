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
struct TYPE_2__ {unsigned int tlb_num_ways; int tlb_num_lines; } ;

/* Variables and functions */
 unsigned long CONFIG_NIOS2_IO_REGION_BASE ; 
 int /*<<< orphan*/  CTL_PTEADDR ; 
 int /*<<< orphan*/  CTL_TLBACC ; 
 int /*<<< orphan*/  CTL_TLBMISC ; 
 unsigned long MAX_PHYS_ADDR ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int TLBMISC_WAY_SHIFT ; 
 unsigned long TLBMISC_WE ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  get_misc_and_pid (unsigned long*,unsigned long*) ; 

void flush_tlb_all(void)
{
	int i;
	unsigned long vaddr = CONFIG_NIOS2_IO_REGION_BASE;
	unsigned int way;
	unsigned long org_misc, pid_misc, tlbmisc;

	/* remember pid/way until we return */
	get_misc_and_pid(&org_misc, &pid_misc);
	pid_misc |= TLBMISC_WE;

	/* Map each TLB entry to physcal address 0 with no-access and a
	   bad ptbase */
	for (way = 0; way < cpuinfo.tlb_num_ways; way++) {
		tlbmisc = pid_misc | (way << TLBMISC_WAY_SHIFT);
		for (i = 0; i < cpuinfo.tlb_num_lines; i++) {
			WRCTL(CTL_PTEADDR, ((vaddr) >> PAGE_SHIFT) << 2);
			WRCTL(CTL_TLBMISC, tlbmisc);
			WRCTL(CTL_TLBACC, (MAX_PHYS_ADDR >> PAGE_SHIFT));
			vaddr += 1UL << 12;
		}
	}

	/* restore pid/way */
	WRCTL(CTL_TLBMISC, org_misc);
}