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
struct IsdnCardState {TYPE_1__* bcs; } ;
struct TYPE_2__ {void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_hdlcstate ; 
 int /*<<< orphan*/  modehdlc (TYPE_1__*,int,int) ; 
 void* setstack_hdlc ; 

__attribute__((used)) static void
inithdlc(struct IsdnCardState *cs)
{
	cs->bcs[0].BC_SetStack = setstack_hdlc;
	cs->bcs[1].BC_SetStack = setstack_hdlc;
	cs->bcs[0].BC_Close = close_hdlcstate;
	cs->bcs[1].BC_Close = close_hdlcstate;
	modehdlc(cs->bcs, -1, 0);
	modehdlc(cs->bcs + 1, -1, 1);
}