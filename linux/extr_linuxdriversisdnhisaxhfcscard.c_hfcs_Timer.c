#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct TYPE_8__ {TYPE_2__ timer; } ;
struct TYPE_9__ {TYPE_3__ hfcD; } ;
struct IsdnCardState {TYPE_4__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; } ;
struct TYPE_10__ {TYPE_1__ hfcD; } ;

/* Variables and functions */
 struct IsdnCardState* cs ; 
 struct IsdnCardState* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_5__ hw ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
hfcs_Timer(struct timer_list *t)
{
	struct IsdnCardState *cs = from_timer(cs, t, hw.hfcD.timer);
	cs->hw.hfcD.timer.expires = jiffies + 75;
	/* WD RESET */
/*	WriteReg(cs, HFCD_DATA, HFCD_CTMT, cs->hw.hfcD.ctmt | 0x80);
	add_timer(&cs->hw.hfcD.timer);
*/
}