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
typedef  int /*<<< orphan*/  u8 ;
struct qib_pportdata {TYPE_1__* cpspec; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {TYPE_2__ chase_timer; scalar_t__ chase_end; } ;

/* Variables and functions */
 scalar_t__ QIB_CHASE_DIS_TIME ; 
 int /*<<< orphan*/  QLOGIC_IB_IBCC_LINKCMD_DOWN ; 
 int /*<<< orphan*/  QLOGIC_IB_IBCC_LINKINITCMD_DISABLE ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  qib_chase ; 
 int /*<<< orphan*/  qib_set_ib_7322_lstate (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_chase(struct qib_pportdata *ppd, unsigned long tnow,
		u8 ibclt)
{
	ppd->cpspec->chase_end = 0;

	if (!qib_chase)
		return;

	qib_set_ib_7322_lstate(ppd, QLOGIC_IB_IBCC_LINKCMD_DOWN,
		QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
	ppd->cpspec->chase_timer.expires = jiffies + QIB_CHASE_DIS_TIME;
	add_timer(&ppd->cpspec->chase_timer);
}