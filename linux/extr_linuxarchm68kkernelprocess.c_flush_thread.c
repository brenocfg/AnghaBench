#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  __USER_DS ; 
 TYPE_2__* current ; 

void flush_thread(void)
{
	current->thread.fs = __USER_DS;
#ifdef CONFIG_FPU
	if (!FPU_IS_EMU) {
		unsigned long zero = 0;
		asm volatile("frestore %0": :"m" (zero));
	}
#endif
}