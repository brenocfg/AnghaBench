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
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int SH_THREAD_UAC_NOPRINT ; 
 int SH_THREAD_UAC_SIGBUS ; 
 unsigned int UM_FIXUP ; 
 unsigned int UM_SIGNAL ; 
 unsigned int UM_WARN ; 
 TYPE_2__* current ; 
 unsigned int se_usermode ; 

unsigned int unaligned_user_action(void)
{
	unsigned int action = se_usermode;

	if (current->thread.flags & SH_THREAD_UAC_SIGBUS) {
		action &= ~UM_FIXUP;
		action |= UM_SIGNAL;
	}

	if (current->thread.flags & SH_THREAD_UAC_NOPRINT)
		action &= ~UM_WARN;

	return action;
}