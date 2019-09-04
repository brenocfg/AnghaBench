#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_hardware_context {scalar_t__ diag_cnt; int /*<<< orphan*/  pci_func; } ;
struct TYPE_2__ {int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {int drv_sds_rings; int drv_tx_rings; int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_CMD_INTRPT_TEST ; 
 int /*<<< orphan*/  QLCNIC_INTERRUPT_TEST ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_interrupt_test (struct net_device*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_diag_alloc_res (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_diag_free_res (struct net_device*,int) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qlcnic_irq_test(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_cmd_args cmd;
	int ret, drv_sds_rings = adapter->drv_sds_rings;
	int drv_tx_rings = adapter->drv_tx_rings;

	if (qlcnic_83xx_check(adapter))
		return qlcnic_83xx_interrupt_test(netdev);

	if (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EIO;

	ret = qlcnic_diag_alloc_res(netdev, QLCNIC_INTERRUPT_TEST);
	if (ret)
		goto clear_diag_irq;

	ahw->diag_cnt = 0;
	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_INTRPT_TEST);
	if (ret)
		goto free_diag_res;

	cmd.req.arg[1] = ahw->pci_func;
	ret = qlcnic_issue_cmd(adapter, &cmd);
	if (ret)
		goto done;

	usleep_range(1000, 12000);
	ret = !ahw->diag_cnt;

done:
	qlcnic_free_mbx_args(&cmd);

free_diag_res:
	qlcnic_diag_free_res(netdev, drv_sds_rings);

clear_diag_irq:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	return ret;
}