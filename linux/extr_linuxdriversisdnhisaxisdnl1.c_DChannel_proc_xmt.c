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
struct TYPE_2__ {int /*<<< orphan*/  (* l1l2 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  Flags; } ;
struct PStack {struct PStack* next; TYPE_1__ l1; } ;
struct IsdnCardState {struct PStack* stlist; scalar_t__ tx_skb; } ;

/* Variables and functions */
 int CONFIRM ; 
 int /*<<< orphan*/  FLG_L1_PULL_REQ ; 
 int PH_PULL ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
DChannel_proc_xmt(struct IsdnCardState *cs)
{
	struct PStack *stptr;

	if (cs->tx_skb)
		return;

	stptr = cs->stlist;
	while (stptr != NULL) {
		if (test_and_clear_bit(FLG_L1_PULL_REQ, &stptr->l1.Flags)) {
			stptr->l1.l1l2(stptr, PH_PULL | CONFIRM, NULL);
			break;
		} else
			stptr = stptr->next;
	}
}