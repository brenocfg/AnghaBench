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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  serio; } ;
struct psmouse {TYPE_1__ ps2dev; } ;
struct byd_data {int touch; int abs_x; int abs_y; struct psmouse* psmouse; } ;

/* Variables and functions */
 int BYD_PAD_HEIGHT ; 
 int BYD_PAD_WIDTH ; 
 int /*<<< orphan*/  byd_report_input (struct psmouse*) ; 
 struct byd_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct byd_data* priv ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void byd_clear_touch(struct timer_list *t)
{
	struct byd_data *priv = from_timer(priv, t, timer);
	struct psmouse *psmouse = priv->psmouse;

	serio_pause_rx(psmouse->ps2dev.serio);
	priv->touch = false;

	byd_report_input(psmouse);

	serio_continue_rx(psmouse->ps2dev.serio);

	/*
	 * Move cursor back to center of pad when we lose touch - this
	 * specifically improves user experience when moving cursor with one
	 * finger, and pressing a button with another.
	 */
	priv->abs_x = BYD_PAD_WIDTH / 2;
	priv->abs_y = BYD_PAD_HEIGHT / 2;
}