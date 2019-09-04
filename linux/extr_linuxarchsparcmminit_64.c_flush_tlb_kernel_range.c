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

/* Variables and functions */
 unsigned long HI_OBP_ADDRESS ; 
 unsigned long LOW_OBP_ADDRESS ; 
 int /*<<< orphan*/  do_flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tsb_kernel_range (unsigned long,unsigned long) ; 

void flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	if (start < HI_OBP_ADDRESS && end > LOW_OBP_ADDRESS) {
		if (start < LOW_OBP_ADDRESS) {
			flush_tsb_kernel_range(start, LOW_OBP_ADDRESS);
			do_flush_tlb_kernel_range(start, LOW_OBP_ADDRESS);
		}
		if (end > HI_OBP_ADDRESS) {
			flush_tsb_kernel_range(HI_OBP_ADDRESS, end);
			do_flush_tlb_kernel_range(HI_OBP_ADDRESS, end);
		}
	} else {
		flush_tsb_kernel_range(start, end);
		do_flush_tlb_kernel_range(start, end);
	}
}