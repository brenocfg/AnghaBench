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
typedef  scalar_t__ u64 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SOFT_RESET_STATUS ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 

int vnic_dev_soft_reset_done(struct vnic_dev *vdev, int *done)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int err;

	*done = 0;

	err = vnic_dev_cmd(vdev, CMD_SOFT_RESET_STATUS, &a0, &a1, wait);
	if (err)
		return err;

	*done = (a0 == 0);

	return 0;
}