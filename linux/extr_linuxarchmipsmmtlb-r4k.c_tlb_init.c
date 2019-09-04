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
struct TYPE_2__ {int tlbsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_tlb_refill_handler () ; 
 TYPE_1__ current_cpu_data ; 
 int ntlb ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  r4k_tlb_configure () ; 
 int /*<<< orphan*/  write_c0_index (int) ; 
 int /*<<< orphan*/  write_c0_wired (int) ; 

void tlb_init(void)
{
	r4k_tlb_configure();

	if (ntlb) {
		if (ntlb > 1 && ntlb <= current_cpu_data.tlbsize) {
			int wired = current_cpu_data.tlbsize - ntlb;
			write_c0_wired(wired);
			write_c0_index(wired-1);
			printk("Restricting TLB to %d entries\n", ntlb);
		} else
			printk("Ignoring invalid argument ntlb=%d\n", ntlb);
	}

	build_tlb_refill_handler();
}