#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct si476x_radio {TYPE_2__* core; int /*<<< orphan*/  ctrl_handler; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; } ;
struct TYPE_6__ {TYPE_1__ power_up_parameters; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI476X_POWER_DOWN ; 
 int /*<<< orphan*/  SI476X_POWER_UP_FULL ; 
 int /*<<< orphan*/  si476x_core_lock (TYPE_2__*) ; 
 int si476x_core_set_power_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si476x_core_unlock (TYPE_2__*) ; 
 int si476x_radio_do_post_powerup_init (struct si476x_radio*,int /*<<< orphan*/ ) ; 
 int si476x_radio_pretune (struct si476x_radio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_fops_open(struct file *file)
{
	struct si476x_radio *radio = video_drvdata(file);
	int err;

	err = v4l2_fh_open(file);
	if (err)
		return err;

	if (v4l2_fh_is_singular_file(file)) {
		si476x_core_lock(radio->core);
		err = si476x_core_set_power_state(radio->core,
						  SI476X_POWER_UP_FULL);
		if (err < 0)
			goto done;

		err = si476x_radio_do_post_powerup_init(radio,
							radio->core->power_up_parameters.func);
		if (err < 0)
			goto power_down;

		err = si476x_radio_pretune(radio,
					   radio->core->power_up_parameters.func);
		if (err < 0)
			goto power_down;

		si476x_core_unlock(radio->core);
		/*Must be done after si476x_core_unlock to prevent a deadlock*/
		v4l2_ctrl_handler_setup(&radio->ctrl_handler);
	}

	return err;

power_down:
	si476x_core_set_power_state(radio->core,
				    SI476X_POWER_DOWN);
done:
	si476x_core_unlock(radio->core);
	v4l2_fh_release(file);

	return err;
}