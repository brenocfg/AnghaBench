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
struct percpu_struct {int type; } ;
struct TYPE_2__ {int processor_offset; } ;

/* Variables and functions */
 unsigned long EV67_CPU ; 
 unsigned long EV69_CPU ; 
 TYPE_1__* hwrpb ; 

__attribute__((used)) static int supported_cpu(void)
{
	struct percpu_struct *cpu;
	unsigned long cputype;

	/* Get cpu type from HW */
	cpu = (struct percpu_struct *)((char *)hwrpb + hwrpb->processor_offset);
	cputype = cpu->type & 0xffffffff;
	/* Include all of EV67, EV68, EV7, EV79 and EV69 as supported. */
	return (cputype >= EV67_CPU) && (cputype <= EV69_CPU);
}