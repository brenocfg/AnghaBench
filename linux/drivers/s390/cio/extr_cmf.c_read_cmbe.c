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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct cmbe {int /*<<< orphan*/  sample_count; int /*<<< orphan*/  initial_command_response_time; int /*<<< orphan*/  device_busy_time; int /*<<< orphan*/  device_active_only_time; int /*<<< orphan*/  control_unit_queuing_time; int /*<<< orphan*/  device_disconnect_time; int /*<<< orphan*/  function_pending_time; int /*<<< orphan*/  device_connect_time; int /*<<< orphan*/  ssch_rsch_count; } ;
struct cmb_data {struct cmbe* hw_block; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmb_start_time; struct cmb_data* cmb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cmb_utilization (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  avg_utilization 137 
#define  cmb_control_unit_queuing_time 136 
#define  cmb_device_active_only_time 135 
#define  cmb_device_busy_time 134 
#define  cmb_device_connect_time 133 
#define  cmb_device_disconnect_time 132 
#define  cmb_function_pending_time 131 
#define  cmb_initial_command_response_time 130 
#define  cmb_sample_count 129 
#define  cmb_ssch_rsch_count 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  time_to_avg_nsec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 read_cmbe(struct ccw_device *cdev, int index)
{
	struct cmb_data *cmb_data;
	unsigned long flags;
	struct cmbe *cmb;
	u64 ret = 0;
	u32 val;

	spin_lock_irqsave(cdev->ccwlock, flags);
	cmb_data = cdev->private->cmb;
	if (!cmb_data)
		goto out;

	cmb = cmb_data->hw_block;
	switch (index) {
	case avg_utilization:
		ret = __cmb_utilization(cmb->device_connect_time,
					cmb->function_pending_time,
					cmb->device_disconnect_time,
					cdev->private->cmb_start_time);
		goto out;
	case cmb_ssch_rsch_count:
		ret = cmb->ssch_rsch_count;
		goto out;
	case cmb_sample_count:
		ret = cmb->sample_count;
		goto out;
	case cmb_device_connect_time:
		val = cmb->device_connect_time;
		break;
	case cmb_function_pending_time:
		val = cmb->function_pending_time;
		break;
	case cmb_device_disconnect_time:
		val = cmb->device_disconnect_time;
		break;
	case cmb_control_unit_queuing_time:
		val = cmb->control_unit_queuing_time;
		break;
	case cmb_device_active_only_time:
		val = cmb->device_active_only_time;
		break;
	case cmb_device_busy_time:
		val = cmb->device_busy_time;
		break;
	case cmb_initial_command_response_time:
		val = cmb->initial_command_response_time;
		break;
	default:
		goto out;
	}
	ret = time_to_avg_nsec(val, cmb->sample_count);
out:
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	return ret;
}