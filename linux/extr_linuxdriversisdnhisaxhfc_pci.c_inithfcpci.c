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
struct IsdnCardState {TYPE_1__* bcs; int /*<<< orphan*/  dbusytimer; } ;
struct TYPE_2__ {void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_hfcpci ; 
 int /*<<< orphan*/  hfcpci_dbusy_timer ; 
 int /*<<< orphan*/  mode_hfcpci (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* setstack_2b ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
inithfcpci(struct IsdnCardState *cs)
{
	cs->bcs[0].BC_SetStack = setstack_2b;
	cs->bcs[1].BC_SetStack = setstack_2b;
	cs->bcs[0].BC_Close = close_hfcpci;
	cs->bcs[1].BC_Close = close_hfcpci;
	timer_setup(&cs->dbusytimer, hfcpci_dbusy_timer, 0);
	mode_hfcpci(cs->bcs, 0, 0);
	mode_hfcpci(cs->bcs + 1, 0, 1);
}