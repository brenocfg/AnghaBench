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
struct vnic_dev {int /*<<< orphan*/  devcmd_rtn; int /*<<< orphan*/  devcmd; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RES_TYPE_DEVCMD ; 
 int /*<<< orphan*/  _vnic_dev_cmd ; 
 int /*<<< orphan*/  vnic_dev_get_res (struct vnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnic_dev_init_devcmd1(struct vnic_dev *vdev)
{
	vdev->devcmd = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD, 0);
	if (!vdev->devcmd)
		return -ENODEV;
	vdev->devcmd_rtn = _vnic_dev_cmd;

	return 0;
}