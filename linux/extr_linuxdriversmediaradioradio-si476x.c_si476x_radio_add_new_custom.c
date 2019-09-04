#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int error; } ;
struct si476x_radio {TYPE_1__ v4l2dev; TYPE_2__ ctrl_handler; } ;
typedef  enum si476x_ctrl_idx { ____Placeholder_si476x_ctrl_idx } si476x_ctrl_idx ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* si476x_ctrls ; 
 struct v4l2_ctrl* v4l2_ctrl_new_custom (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si476x_radio_add_new_custom(struct si476x_radio *radio,
				       enum si476x_ctrl_idx idx)
{
	int rval;
	struct v4l2_ctrl *ctrl;

	ctrl = v4l2_ctrl_new_custom(&radio->ctrl_handler,
				    &si476x_ctrls[idx],
				    NULL);
	rval = radio->ctrl_handler.error;
	if (ctrl == NULL && rval)
		dev_err(radio->v4l2dev.dev,
			"Could not initialize '%s' control %d\n",
			si476x_ctrls[idx].name, rval);

	return rval;
}