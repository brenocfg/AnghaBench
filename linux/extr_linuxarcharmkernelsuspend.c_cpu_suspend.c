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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int __cpu_suspend (unsigned long,int (*) (unsigned long),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_logical_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int cpu_suspend(unsigned long arg, int (*fn)(unsigned long))
{
	u32 __mpidr = cpu_logical_map(smp_processor_id());
	return __cpu_suspend(arg, fn, __mpidr);
}