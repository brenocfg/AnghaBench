#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct qlcnic_info {int bit_offsets; int min_tx_bw; int max_tx_bw; int max_tx_ques; int max_tx_mac_filters; int max_rx_mcast_mac_filters; int max_rx_ucast_mac_filters; int max_rx_ip_addr; int max_rx_lro_flow; int max_rx_status_rings; int max_rx_buf_rings; int max_rx_ques; int max_tx_vlan_keys; int max_local_ipv6_addrs; int max_remote_ipv6_addrs; } ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_CMD_SET_NIC_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_set_vport_info(struct qlcnic_adapter *adapter,
					  struct qlcnic_info *npar_info,
					  u16 vport_id)
{
	struct qlcnic_cmd_args cmd;
	int err;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO))
		return -ENOMEM;

	cmd.req.arg[1] = (vport_id << 16) | 0x1;
	cmd.req.arg[2] = npar_info->bit_offsets;
	cmd.req.arg[2] |= npar_info->min_tx_bw << 16;
	cmd.req.arg[3] = npar_info->max_tx_bw | (npar_info->max_tx_ques << 16);
	cmd.req.arg[4] = npar_info->max_tx_mac_filters;
	cmd.req.arg[4] |= npar_info->max_rx_mcast_mac_filters << 16;
	cmd.req.arg[5] = npar_info->max_rx_ucast_mac_filters |
			 (npar_info->max_rx_ip_addr << 16);
	cmd.req.arg[6] = npar_info->max_rx_lro_flow |
			 (npar_info->max_rx_status_rings << 16);
	cmd.req.arg[7] = npar_info->max_rx_buf_rings |
			 (npar_info->max_rx_ques << 16);
	cmd.req.arg[8] = npar_info->max_tx_vlan_keys;
	cmd.req.arg[8] |= npar_info->max_local_ipv6_addrs << 16;
	cmd.req.arg[9] = npar_info->max_remote_ipv6_addrs;

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err)
		dev_err(&adapter->pdev->dev,
			"Failed to set vport info, err=%d\n", err);

	qlcnic_free_mbx_args(&cmd);
	return err;
}