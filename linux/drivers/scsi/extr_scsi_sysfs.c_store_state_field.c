#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  request_queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;
struct TYPE_3__ {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
#define  SDEV_OFFLINE 129 
#define  SDEV_RUNNING 128 
 int /*<<< orphan*/  blk_mq_run_hw_queues (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scsi_device_set_state (struct scsi_device*,int) ; 
 TYPE_1__* sdev_states ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int const) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
store_state_field(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	int i, ret;
	struct scsi_device *sdev = to_scsi_device(dev);
	enum scsi_device_state state = 0;

	for (i = 0; i < ARRAY_SIZE(sdev_states); i++) {
		const int len = strlen(sdev_states[i].name);
		if (strncmp(sdev_states[i].name, buf, len) == 0 &&
		   buf[len] == '\n') {
			state = sdev_states[i].value;
			break;
		}
	}
	switch (state) {
	case SDEV_RUNNING:
	case SDEV_OFFLINE:
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&sdev->state_mutex);
	ret = scsi_device_set_state(sdev, state);
	/*
	 * If the device state changes to SDEV_RUNNING, we need to run
	 * the queue to avoid I/O hang.
	 */
	if (ret == 0 && state == SDEV_RUNNING)
		blk_mq_run_hw_queues(sdev->request_queue, true);
	mutex_unlock(&sdev->state_mutex);

	return ret == 0 ? count : -EINVAL;
}