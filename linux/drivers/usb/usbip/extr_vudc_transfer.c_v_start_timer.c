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
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct transfer_timer {int state; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  frame_start; } ;
struct vudc {TYPE_1__ gadget; TYPE_2__* pdev; struct transfer_timer tr_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  VUDC_TR_IDLE 130 
#define  VUDC_TR_RUNNING 129 
#define  VUDC_TR_STOPPED 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_frame_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 void v_kick_timer (struct vudc*,int /*<<< orphan*/ ) ; 

void v_start_timer(struct vudc *udc)
{
	struct transfer_timer *t = &udc->tr_timer;

	dev_dbg(&udc->pdev->dev, "timer start");
	switch (t->state) {
	case VUDC_TR_RUNNING:
		return;
	case VUDC_TR_IDLE:
		return v_kick_timer(udc, jiffies);
	case VUDC_TR_STOPPED:
		t->state = VUDC_TR_IDLE;
		t->frame_start = jiffies;
		t->frame_limit = get_frame_limit(udc->gadget.speed);
		return v_kick_timer(udc, jiffies);
	}
}