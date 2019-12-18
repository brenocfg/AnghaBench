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
typedef  int /*<<< orphan*/  up_ver ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_version_info {char* ver; scalar_t__ status; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_MGMT_VERSION_MAX_LEN ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_GET_MGMT_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_version_info*,int,struct hinic_version_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

int hinic_get_mgmt_version(struct hinic_dev *nic_dev, u8 *mgmt_ver)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_version_info up_ver = {0};
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u16 out_size;
	int err;

	if (!hwdev)
		return -EINVAL;

	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_MGMT_VERSION,
				 &up_ver, sizeof(up_ver), &up_ver,
				 &out_size);
	if (err || !out_size || up_ver.status) {
		dev_err(&pdev->dev,
			"Failed to get mgmt version, err: %d, status: 0x%x, out size: 0x%x\n",
			err, up_ver.status, out_size);
		return -EINVAL;
	}

	snprintf(mgmt_ver, HINIC_MGMT_VERSION_MAX_LEN, "%s", up_ver.ver);

	return 0;
}