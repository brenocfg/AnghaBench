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
struct serio {TYPE_1__* drv; } ;
struct rmi_function {int /*<<< orphan*/  dev; } ;
struct f03_data {int /*<<< orphan*/  overwrite_buttons; struct serio* serio; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* interrupt ) (struct serio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_OOB_EXTRA_BTNS ; 
 int /*<<< orphan*/  SERIO_OOB_DATA ; 
 struct f03_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_continue_rx (struct serio*) ; 
 int /*<<< orphan*/  serio_pause_rx (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct serio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct serio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rmi_f03_commit_buttons(struct rmi_function *fn)
{
	struct f03_data *f03 = dev_get_drvdata(&fn->dev);
	struct serio *serio = f03->serio;

	serio_pause_rx(serio);
	if (serio->drv) {
		serio->drv->interrupt(serio, PSMOUSE_OOB_EXTRA_BTNS,
				      SERIO_OOB_DATA);
		serio->drv->interrupt(serio, f03->overwrite_buttons,
				      SERIO_OOB_DATA);
	}
	serio_continue_rx(serio);
}