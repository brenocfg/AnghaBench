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
struct TYPE_5__ {TYPE_1__* aux_dpfp; } ;
struct TYPE_6__ {TYPE_2__ fpu; } ;
struct task_struct {TYPE_3__ thread; } ;
struct TYPE_4__ {unsigned int l; } ;

/* Variables and functions */

void fpu_save_restore(struct task_struct *prev, struct task_struct *next)
{
	unsigned int *saveto = &prev->thread.fpu.aux_dpfp[0].l;
	unsigned int *readfrom = &next->thread.fpu.aux_dpfp[0].l;

	const unsigned int zero = 0;

	__asm__ __volatile__(
		"daddh11  %0, %2, %2\n"
		"dexcl1   %1, %3, %4\n"
		: "=&r" (*(saveto + 1)), /* early clobber must here */
		  "=&r" (*(saveto))
		: "r" (zero), "r" (*(readfrom + 1)), "r" (*(readfrom))
	);

	__asm__ __volatile__(
		"daddh22  %0, %2, %2\n"
		"dexcl2   %1, %3, %4\n"
		: "=&r"(*(saveto + 3)),	/* early clobber must here */
		  "=&r"(*(saveto + 2))
		: "r" (zero), "r" (*(readfrom + 3)), "r" (*(readfrom + 2))
	);
}