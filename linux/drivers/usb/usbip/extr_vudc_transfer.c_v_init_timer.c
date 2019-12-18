#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct transfer_timer {int /*<<< orphan*/  state; int /*<<< orphan*/  timer; } ;
struct vudc {struct transfer_timer tr_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  VUDC_TR_STOPPED ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_timer ; 

void v_init_timer(struct vudc *udc)
{
	struct transfer_timer *t = &udc->tr_timer;

	timer_setup(&t->timer, v_timer, 0);
	t->state = VUDC_TR_STOPPED;
}