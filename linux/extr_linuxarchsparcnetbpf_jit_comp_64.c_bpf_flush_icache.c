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
 int /*<<< orphan*/  flushi (unsigned long) ; 
 scalar_t__ spitfire ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static void bpf_flush_icache(void *start_, void *end_)
{
	/* Cheetah's I-cache is fully coherent.  */
	if (tlb_type == spitfire) {
		unsigned long start = (unsigned long) start_;
		unsigned long end = (unsigned long) end_;

		start &= ~7UL;
		end = (end + 7UL) & ~7UL;
		while (start < end) {
			flushi(start);
			start += 32;
		}
	}
}