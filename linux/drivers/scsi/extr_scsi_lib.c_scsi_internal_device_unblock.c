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
struct scsi_device {int /*<<< orphan*/  state_mutex; } ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scsi_internal_device_unblock_nowait (struct scsi_device*,int) ; 

__attribute__((used)) static int scsi_internal_device_unblock(struct scsi_device *sdev,
					enum scsi_device_state new_state)
{
	int ret;

	mutex_lock(&sdev->state_mutex);
	ret = scsi_internal_device_unblock_nowait(sdev, new_state);
	mutex_unlock(&sdev->state_mutex);

	return ret;
}