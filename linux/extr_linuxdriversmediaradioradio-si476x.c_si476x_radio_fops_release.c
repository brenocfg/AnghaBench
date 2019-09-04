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
struct si476x_radio {TYPE_1__* core; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI476X_POWER_DOWN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si476x_core_set_power_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_release (struct file*) ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_fops_release(struct file *file)
{
	int err;
	struct si476x_radio *radio = video_drvdata(file);

	if (v4l2_fh_is_singular_file(file) &&
	    atomic_read(&radio->core->is_alive))
		si476x_core_set_power_state(radio->core,
					    SI476X_POWER_DOWN);

	err = v4l2_fh_release(file);

	return err;
}