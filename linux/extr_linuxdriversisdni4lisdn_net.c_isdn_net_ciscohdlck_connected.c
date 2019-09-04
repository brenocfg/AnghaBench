#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ expires; } ;
struct TYPE_6__ {int cisco_keepalive_period; TYPE_2__ cisco_timer; scalar_t__ cisco_debserint; scalar_t__ cisco_line_state; scalar_t__ cisco_last_slarp_in; scalar_t__ cisco_yourseq; scalar_t__ cisco_mineseen; scalar_t__ cisco_myseq; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 int HZ ; 
 int ISDN_TIMER_KEEPINT ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  isdn_net_ciscohdlck_slarp_send_keepalive ; 
 int /*<<< orphan*/  isdn_net_ciscohdlck_slarp_send_request (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdn_net_ciscohdlck_connected(isdn_net_local *lp)
{
	lp->cisco_myseq = 0;
	lp->cisco_mineseen = 0;
	lp->cisco_yourseq = 0;
	lp->cisco_keepalive_period = ISDN_TIMER_KEEPINT;
	lp->cisco_last_slarp_in = 0;
	lp->cisco_line_state = 0;
	lp->cisco_debserint = 0;

	/* send slarp request because interface/seq.no.s reset */
	isdn_net_ciscohdlck_slarp_send_request(lp);

	timer_setup(&lp->cisco_timer,
		    isdn_net_ciscohdlck_slarp_send_keepalive, 0);
	lp->cisco_timer.expires = jiffies + lp->cisco_keepalive_period * HZ;
	add_timer(&lp->cisco_timer);
}