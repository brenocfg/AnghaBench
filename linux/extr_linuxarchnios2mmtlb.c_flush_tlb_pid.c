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
struct TYPE_2__ {unsigned int tlb_num_lines; unsigned int tlb_num_ways; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_PTEADDR ; 
 int /*<<< orphan*/  CTL_TLBACC ; 
 int /*<<< orphan*/  CTL_TLBMISC ; 
 unsigned long MAX_PHYS_ADDR ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long RDCTL (int /*<<< orphan*/ ) ; 
 unsigned long TLBMISC_PID_MASK ; 
 unsigned long TLBMISC_PID_SHIFT ; 
 unsigned long TLBMISC_RD ; 
 unsigned int TLBMISC_WAY_SHIFT ; 
 unsigned long TLBMISC_WE ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  get_misc_and_pid (unsigned long*,unsigned long*) ; 

void flush_tlb_pid(unsigned long pid)
{
	unsigned int line;
	unsigned int way;
	unsigned long org_misc, pid_misc;

	/* remember pid/way until we return */
	get_misc_and_pid(&org_misc, &pid_misc);

	for (line = 0; line < cpuinfo.tlb_num_lines; line++) {
		WRCTL(CTL_PTEADDR, line << 2);

		for (way = 0; way < cpuinfo.tlb_num_ways; way++) {
			unsigned long pteaddr;
			unsigned long tlbmisc;
			unsigned long tlbacc;

			tlbmisc = pid_misc | TLBMISC_RD |
				(way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			pteaddr = RDCTL(CTL_PTEADDR);
			tlbmisc = RDCTL(CTL_TLBMISC);
			tlbacc = RDCTL(CTL_TLBACC);

			if (((tlbmisc>>TLBMISC_PID_SHIFT) & TLBMISC_PID_MASK)
				== pid) {
				tlbmisc = pid_misc | TLBMISC_WE |
					(way << TLBMISC_WAY_SHIFT);
				WRCTL(CTL_TLBMISC, tlbmisc);
				WRCTL(CTL_TLBACC,
					(MAX_PHYS_ADDR >> PAGE_SHIFT));
			}
		}

		WRCTL(CTL_TLBMISC, org_misc);
	}
}