#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct qlcnic_info {void* max_remote_ipv6_addrs; void* max_local_ipv6_addrs; void* max_tx_vlan_keys; void* max_rx_ques; void* max_rx_buf_rings; void* max_rx_status_rings; void* max_rx_lro_flow; void* max_rx_ip_addr; void* max_rx_ucast_mac_filters; void* max_rx_mcast_mac_filters; void* max_tx_mac_filters; void* max_tx_ques; void* max_tx_bw; void* min_tx_bw; } ;
struct TYPE_6__ {int* arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int BIT_8 ; 
 int BIT_9 ; 
 void* LSW (int) ; 
 void* MSW (int) ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_NIC_INFO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_sriov_get_vf_vport_info(struct qlcnic_adapter *adapter,
				   struct qlcnic_info *npar_info, u16 vport_id)
{
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_cmd_args cmd;
	int err;
	u32 status;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO);
	if (err)
		return err;

	cmd.req.arg[1] = vport_id << 16 | 0x1;
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_err(&adapter->pdev->dev,
			"Failed to get vport info, err=%d\n", err);
		qlcnic_free_mbx_args(&cmd);
		return err;
	}

	status = cmd.rsp.arg[2] & 0xffff;
	if (status & BIT_0)
		npar_info->min_tx_bw = MSW(cmd.rsp.arg[2]);
	if (status & BIT_1)
		npar_info->max_tx_bw = LSW(cmd.rsp.arg[3]);
	if (status & BIT_2)
		npar_info->max_tx_ques = MSW(cmd.rsp.arg[3]);
	if (status & BIT_3)
		npar_info->max_tx_mac_filters = LSW(cmd.rsp.arg[4]);
	if (status & BIT_4)
		npar_info->max_rx_mcast_mac_filters = MSW(cmd.rsp.arg[4]);
	if (status & BIT_5)
		npar_info->max_rx_ucast_mac_filters = LSW(cmd.rsp.arg[5]);
	if (status & BIT_6)
		npar_info->max_rx_ip_addr = MSW(cmd.rsp.arg[5]);
	if (status & BIT_7)
		npar_info->max_rx_lro_flow = LSW(cmd.rsp.arg[6]);
	if (status & BIT_8)
		npar_info->max_rx_status_rings = MSW(cmd.rsp.arg[6]);
	if (status & BIT_9)
		npar_info->max_rx_buf_rings = LSW(cmd.rsp.arg[7]);

	npar_info->max_rx_ques = MSW(cmd.rsp.arg[7]);
	npar_info->max_tx_vlan_keys = LSW(cmd.rsp.arg[8]);
	npar_info->max_local_ipv6_addrs = MSW(cmd.rsp.arg[8]);
	npar_info->max_remote_ipv6_addrs = LSW(cmd.rsp.arg[9]);

	dev_info(dev, "\n\tmin_tx_bw: %d, max_tx_bw: %d max_tx_ques: %d,\n"
		 "\tmax_tx_mac_filters: %d max_rx_mcast_mac_filters: %d,\n"
		 "\tmax_rx_ucast_mac_filters: 0x%x, max_rx_ip_addr: %d,\n"
		 "\tmax_rx_lro_flow: %d max_rx_status_rings: %d,\n"
		 "\tmax_rx_buf_rings: %d, max_rx_ques: %d, max_tx_vlan_keys %d\n"
		 "\tlocal_ipv6_addr: %d, remote_ipv6_addr: %d\n",
		 npar_info->min_tx_bw, npar_info->max_tx_bw,
		 npar_info->max_tx_ques, npar_info->max_tx_mac_filters,
		 npar_info->max_rx_mcast_mac_filters,
		 npar_info->max_rx_ucast_mac_filters, npar_info->max_rx_ip_addr,
		 npar_info->max_rx_lro_flow, npar_info->max_rx_status_rings,
		 npar_info->max_rx_buf_rings, npar_info->max_rx_ques,
		 npar_info->max_tx_vlan_keys, npar_info->max_local_ipv6_addrs,
		 npar_info->max_remote_ipv6_addrs);

	qlcnic_free_mbx_args(&cmd);
	return err;
}