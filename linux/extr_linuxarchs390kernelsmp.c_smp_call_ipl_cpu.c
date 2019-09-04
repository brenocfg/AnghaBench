#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lowcore {scalar_t__ panic_stack; } ;
struct TYPE_3__ {scalar_t__ address; struct lowcore* lowcore; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PANIC_FRAME_OFFSET ; 
 struct lowcore S390_lowcore ; 
 int /*<<< orphan*/  pcpu_delegate (TYPE_1__*,void (*) (void*),void*,scalar_t__) ; 
 TYPE_1__* pcpu_devices ; 
 scalar_t__ stap () ; 

void smp_call_ipl_cpu(void (*func)(void *), void *data)
{
	struct lowcore *lc = pcpu_devices->lowcore;

	if (pcpu_devices[0].address == stap())
		lc = &S390_lowcore;

	pcpu_delegate(&pcpu_devices[0], func, data,
		      lc->panic_stack - PANIC_FRAME_OFFSET + PAGE_SIZE);
}