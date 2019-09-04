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
struct IsdnCardState {TYPE_3__* bcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ftimer; } ;
struct TYPE_5__ {TYPE_1__ isar; } ;
struct TYPE_6__ {TYPE_2__ hw; void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_isarstate ; 
 int /*<<< orphan*/  ftimer_handler ; 
 void* setstack_isar ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void initisar(struct IsdnCardState *cs)
{
	cs->bcs[0].BC_SetStack = setstack_isar;
	cs->bcs[1].BC_SetStack = setstack_isar;
	cs->bcs[0].BC_Close = close_isarstate;
	cs->bcs[1].BC_Close = close_isarstate;
	timer_setup(&cs->bcs[0].hw.isar.ftimer, ftimer_handler, 0);
	timer_setup(&cs->bcs[1].hw.isar.ftimer, ftimer_handler, 0);
}