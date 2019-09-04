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
typedef  int /*<<< orphan*/  u64 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ENABLE ; 
 int /*<<< orphan*/  CMD_ENABLE_WAIT ; 
 scalar_t__ vnic_dev_capable (struct vnic_dev*,int /*<<< orphan*/ ) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int vnic_dev_enable_wait(struct vnic_dev *vdev)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;

	if (vnic_dev_capable(vdev, CMD_ENABLE_WAIT))
		return vnic_dev_cmd(vdev, CMD_ENABLE_WAIT, &a0, &a1, wait);
	else
		return vnic_dev_cmd(vdev, CMD_ENABLE, &a0, &a1, wait);
}