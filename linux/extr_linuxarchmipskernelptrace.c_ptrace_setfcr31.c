#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int fcr31; } ;
struct TYPE_5__ {TYPE_1__ fpu; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_6__ {int fpu_msk31; } ;

/* Variables and functions */
 TYPE_3__ boot_cpu_data ; 

__attribute__((used)) static void ptrace_setfcr31(struct task_struct *child, u32 value)
{
	u32 fcr31;
	u32 mask;

	fcr31 = child->thread.fpu.fcr31;
	mask = boot_cpu_data.fpu_msk31;
	child->thread.fpu.fcr31 = (value & ~mask) | (fcr31 & mask);
}