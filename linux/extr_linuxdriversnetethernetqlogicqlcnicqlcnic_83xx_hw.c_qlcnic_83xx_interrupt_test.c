#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qlcnic_hardware_context {scalar_t__ diag_cnt; TYPE_1__* intr_tbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * arg; } ;
struct TYPE_6__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; TYPE_2__ req; } ;
struct qlcnic_adapter {int flags; void* drv_tx_rings; void* drv_sds_rings; TYPE_4__* pdev; int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int id; } ;

/* Variables and functions */
 int BIT_0 ; 
 int EBUSY ; 
 void* LSB (int /*<<< orphan*/ ) ; 
 int LSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CMD_INTRPT_TEST ; 
 int /*<<< orphan*/  QLCNIC_DEF_INT_ID ; 
 int /*<<< orphan*/  QLCNIC_INTERRUPT_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_83xx_diag_alloc_res (struct net_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  qlcnic_83xx_diag_free_res (struct net_device*,void*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 scalar_t__ qlcnic_get_diag_lock (struct qlcnic_adapter*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_release_diag_lock (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_83xx_interrupt_test(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_cmd_args cmd;
	u8 val, drv_sds_rings = adapter->drv_sds_rings;
	u8 drv_tx_rings = adapter->drv_tx_rings;
	u32 data;
	u16 intrpt_id, id;
	int ret;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state)) {
		netdev_info(netdev, "Device is resetting\n");
		return -EBUSY;
	}

	if (qlcnic_get_diag_lock(adapter)) {
		netdev_info(netdev, "Device in diagnostics mode\n");
		return -EBUSY;
	}

	ret = qlcnic_83xx_diag_alloc_res(netdev, QLCNIC_INTERRUPT_TEST,
					 drv_sds_rings);
	if (ret)
		goto fail_diag_irq;

	ahw->diag_cnt = 0;
	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_INTRPT_TEST);
	if (ret)
		goto fail_diag_irq;

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		intrpt_id = ahw->intr_tbl[0].id;
	else
		intrpt_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);

	cmd.req.arg[1] = 1;
	cmd.req.arg[2] = intrpt_id;
	cmd.req.arg[3] = BIT_0;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	data = cmd.rsp.arg[2];
	id = LSW(data);
	val = LSB(MSW(data));
	if (id != intrpt_id)
		dev_info(&adapter->pdev->dev,
			 "Interrupt generated: 0x%x, requested:0x%x\n",
			 id, intrpt_id);
	if (val)
		dev_err(&adapter->pdev->dev,
			 "Interrupt test error: 0x%x\n", val);
	if (ret)
		goto done;

	msleep(20);
	ret = !ahw->diag_cnt;

done:
	qlcnic_free_mbx_args(&cmd);
	qlcnic_83xx_diag_free_res(netdev, drv_sds_rings);

fail_diag_irq:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	qlcnic_release_diag_lock(adapter);
	return ret;
}