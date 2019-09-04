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
struct cpuinfo_mips {int tlbsize; } ;

/* Variables and functions */
 struct cpuinfo_mips current_cpu_data ; 

__attribute__((used)) static void probe_tlb(unsigned long config)
{
	struct cpuinfo_mips *c = &current_cpu_data;

	c->tlbsize = 3 * 128;		/* 3 sets each 128 entries */
}