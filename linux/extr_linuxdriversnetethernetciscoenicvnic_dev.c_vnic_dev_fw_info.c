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
struct vnic_devcmd_fw_info {int dummy; } ;
struct vnic_dev {int fw_info_pa; struct vnic_devcmd_fw_info* fw_info; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MCPU_FW_INFO ; 
 int /*<<< orphan*/  CMD_MCPU_FW_INFO_OLD ; 
 int ENOMEM ; 
 struct vnic_devcmd_fw_info* pci_zalloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ vnic_dev_capable (struct vnic_dev*,int /*<<< orphan*/ ) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int*,int*,int) ; 

int vnic_dev_fw_info(struct vnic_dev *vdev,
	struct vnic_devcmd_fw_info **fw_info)
{
	u64 a0, a1 = 0;
	int wait = 1000;
	int err = 0;

	if (!vdev->fw_info) {
		vdev->fw_info = pci_zalloc_consistent(vdev->pdev,
						      sizeof(struct vnic_devcmd_fw_info),
						      &vdev->fw_info_pa);
		if (!vdev->fw_info)
			return -ENOMEM;

		a0 = vdev->fw_info_pa;
		a1 = sizeof(struct vnic_devcmd_fw_info);

		/* only get fw_info once and cache it */
		if (vnic_dev_capable(vdev, CMD_MCPU_FW_INFO))
			err = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO,
				&a0, &a1, wait);
		else
			err = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO_OLD,
				&a0, &a1, wait);
	}

	*fw_info = vdev->fw_info;

	return err;
}