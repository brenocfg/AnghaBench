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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_pfhwdev {struct hinic_nic_cb* nic_cb; struct hinic_hwdev hwdev; } ;
struct hinic_nic_cb {int cb_state; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;
struct hinic_hwif {struct pci_dev* pdev; } ;
typedef  enum hinic_cb_state { ____Placeholder_hinic_cb_state } hinic_cb_state ;

/* Variables and functions */
 int HINIC_CB_ENABLED ; 
 int HINIC_CB_RUNNING ; 
 size_t HINIC_MGMT_MSG_CMD_BASE ; 
 size_t HINIC_MGMT_MSG_CMD_MAX ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nic_mgmt_msg_handler(void *handle, u8 cmd, void *buf_in,
				 u16 in_size, void *buf_out, u16 *out_size)
{
	struct hinic_pfhwdev *pfhwdev = handle;
	enum hinic_cb_state cb_state;
	struct hinic_nic_cb *nic_cb;
	struct hinic_hwdev *hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u8 cmd_cb;

	hwdev = &pfhwdev->hwdev;
	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	if ((cmd < HINIC_MGMT_MSG_CMD_BASE) ||
	    (cmd >= HINIC_MGMT_MSG_CMD_MAX)) {
		dev_err(&pdev->dev, "unknown L2NIC event, cmd = %d\n", cmd);
		return;
	}

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;

	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	cb_state = cmpxchg(&nic_cb->cb_state,
			   HINIC_CB_ENABLED,
			   HINIC_CB_ENABLED | HINIC_CB_RUNNING);

	if ((cb_state == HINIC_CB_ENABLED) && (nic_cb->handler))
		nic_cb->handler(nic_cb->handle, buf_in,
				in_size, buf_out, out_size);
	else
		dev_err(&pdev->dev, "Unhandled NIC Event %d\n", cmd);

	nic_cb->cb_state &= ~HINIC_CB_RUNNING;
}