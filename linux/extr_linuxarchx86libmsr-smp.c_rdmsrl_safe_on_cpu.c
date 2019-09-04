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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int rdmsr_safe_on_cpu (unsigned int,int,int*,int*) ; 

int rdmsrl_safe_on_cpu(unsigned int cpu, u32 msr_no, u64 *q)
{
	u32 low, high;
	int err;

	err = rdmsr_safe_on_cpu(cpu, msr_no, &low, &high);
	*q = (u64)high << 32 | low;

	return err;
}