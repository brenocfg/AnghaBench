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
struct transfer_timer {int state; int /*<<< orphan*/  timer; } ;
struct vudc {TYPE_1__* pdev; struct transfer_timer tr_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  VUDC_TR_IDLE 130 
#define  VUDC_TR_RUNNING 129 
#define  VUDC_TR_STOPPED 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 

void v_kick_timer(struct vudc *udc, unsigned long time)
{
	struct transfer_timer *t = &udc->tr_timer;

	dev_dbg(&udc->pdev->dev, "timer kick");
	switch (t->state) {
	case VUDC_TR_RUNNING:
		return;
	case VUDC_TR_IDLE:
		t->state = VUDC_TR_RUNNING;
		/* fallthrough */
	case VUDC_TR_STOPPED:
		/* we may want to kick timer to unqueue urbs */
		mod_timer(&t->timer, time);
	}
}