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
struct TYPE_4__ {int /*<<< orphan*/ * function; } ;
struct TYPE_3__ {scalar_t__ l1; TYPE_2__ timer; } ;
struct isac_hw {int type; TYPE_1__ dch; int /*<<< orphan*/ * mon_tx; int /*<<< orphan*/ * mon_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_CHANNEL ; 
 int IPAC_TYPE_ISACX ; 
 int /*<<< orphan*/  ISACX_MASK ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l1_event (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_freedchannel (TYPE_1__*) ; 

__attribute__((used)) static void
isac_release(struct isac_hw *isac)
{
	if (isac->type & IPAC_TYPE_ISACX)
		WriteISAC(isac, ISACX_MASK, 0xff);
	else
		WriteISAC(isac, ISAC_MASK, 0xff);
	if (isac->dch.timer.function != NULL) {
		del_timer(&isac->dch.timer);
		isac->dch.timer.function = NULL;
	}
	kfree(isac->mon_rx);
	isac->mon_rx = NULL;
	kfree(isac->mon_tx);
	isac->mon_tx = NULL;
	if (isac->dch.l1)
		l1_event(isac->dch.l1, CLOSE_CHANNEL);
	mISDN_freedchannel(&isac->dch);
}