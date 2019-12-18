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
struct iio_trigger {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct iio_loop_info {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_loop_thread ; 
 struct iio_loop_info* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct iio_trigger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iio_loop_trigger_set_state(struct iio_trigger *trig, bool state)
{
	struct iio_loop_info *loop_trig = iio_trigger_get_drvdata(trig);

	if (state) {
		loop_trig->task = kthread_run(iio_loop_thread,
					      trig, trig->name);
		if (IS_ERR(loop_trig->task)) {
			dev_err(&trig->dev,
				"failed to create trigger loop thread\n");
			return PTR_ERR(loop_trig->task);
		}
	} else {
		kthread_stop(loop_trig->task);
	}

	return 0;
}