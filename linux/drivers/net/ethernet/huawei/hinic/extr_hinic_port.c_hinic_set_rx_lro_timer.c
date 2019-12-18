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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_lro_timer {int status; int enable; int /*<<< orphan*/  timer; scalar_t__ type; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  lro_timer ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_LRO_TIMER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_lro_timer*,int,struct hinic_lro_timer*,int*) ; 

__attribute__((used)) static int hinic_set_rx_lro_timer(struct hinic_dev *nic_dev, u32 timer_value)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_lro_timer lro_timer = { 0 };
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size = sizeof(lro_timer);
	int err;

	lro_timer.status = 0;
	lro_timer.type = 0;
	lro_timer.enable = 1;
	lro_timer.timer = timer_value;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_LRO_TIMER,
				 &lro_timer, sizeof(lro_timer),
				 &lro_timer, &out_size);
	if (lro_timer.status == 0xFF) {
		/* For this case, we think status (0xFF) is OK */
		lro_timer.status = 0;
		dev_dbg(&pdev->dev,
			"Set lro timer not supported by the current FW version, it will be 1ms default\n");
	}

	if (err || !out_size || lro_timer.status) {
		dev_err(&pdev->dev,
			"Failed to set lro timer, ret = %d\n",
			lro_timer.status);

		return -EINVAL;
	}

	return 0;
}