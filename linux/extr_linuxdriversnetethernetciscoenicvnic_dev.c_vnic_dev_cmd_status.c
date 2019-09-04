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
typedef  int u64 ;
struct vnic_dev {int dummy; } ;
typedef  enum vnic_devcmd_cmd { ____Placeholder_vnic_devcmd_cmd } vnic_devcmd_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATUS ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int*,int*,int) ; 

__attribute__((used)) static int vnic_dev_cmd_status(struct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
	int *status)
{
	u64 a0 = cmd, a1 = 0;
	int wait = 1000;
	int ret;

	ret = vnic_dev_cmd(vdev, CMD_STATUS, &a0, &a1, wait);
	if (!ret)
		*status = (int)a0;

	return ret;
}