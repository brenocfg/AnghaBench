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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; TYPE_2__* ahw; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  vxlan_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_INIT_NIC_FUNC ; 
 int QLC_83XX_ENCAP_TYPE_VXLAN ; 
 int QLC_83XX_MULTI_TENANCY_INFO ; 
 int QLC_83XX_SET_VXLAN_UDP_DPORT ; 
 int QLC_83XX_VXLAN_UDP_DPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlcnic_cmd_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_set_vxlan_port(struct qlcnic_adapter *adapter)
{
	u16 port = adapter->ahw->vxlan_port;
	struct qlcnic_cmd_args cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));

	ret = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_INIT_NIC_FUNC);
	if (ret)
		return ret;

	cmd.req.arg[1] = QLC_83XX_MULTI_TENANCY_INFO;
	cmd.req.arg[2] = QLC_83XX_ENCAP_TYPE_VXLAN |
			 QLC_83XX_SET_VXLAN_UDP_DPORT |
			 QLC_83XX_VXLAN_UDP_DPORT(port);

	ret = qlcnic_issue_cmd(adapter, &cmd);
	if (ret)
		netdev_err(adapter->netdev,
			   "Failed to set VXLAN port %d in adapter\n",
			   port);

	qlcnic_free_mbx_args(&cmd);

	return ret;
}