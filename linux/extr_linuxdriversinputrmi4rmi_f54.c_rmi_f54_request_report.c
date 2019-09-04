#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  command_base_addr; } ;
struct rmi_function {TYPE_3__ fd; struct rmi_device* rmi_dev; int /*<<< orphan*/  dev; } ;
struct rmi_device {int dummy; } ;
struct f54_data {int is_busy; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; scalar_t__ timeout; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  report_type; TYPE_2__* fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_base_addr; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  F54_GET_REPORT ; 
 struct f54_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rmi_write (struct rmi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rmi_f54_request_report(struct rmi_function *fn, u8 report_type)
{
	struct f54_data *f54 = dev_get_drvdata(&fn->dev);
	struct rmi_device *rmi_dev = fn->rmi_dev;
	int error;

	/* Write Report Type into F54_AD_Data0 */
	if (f54->report_type != report_type) {
		error = rmi_write(rmi_dev, f54->fn->fd.data_base_addr,
				  report_type);
		if (error)
			return error;
		f54->report_type = report_type;
	}

	/*
	 * Small delay after disabling interrupts to avoid race condition
	 * in firmare. This value is a bit higher than absolutely necessary.
	 * Should be removed once issue is resolved in firmware.
	 */
	usleep_range(2000, 3000);

	mutex_lock(&f54->data_mutex);

	error = rmi_write(rmi_dev, fn->fd.command_base_addr, F54_GET_REPORT);
	if (error < 0)
		goto unlock;

	init_completion(&f54->cmd_done);

	f54->is_busy = 1;
	f54->timeout = jiffies + msecs_to_jiffies(100);

	queue_delayed_work(f54->workqueue, &f54->work, 0);

unlock:
	mutex_unlock(&f54->data_mutex);

	return error;
}