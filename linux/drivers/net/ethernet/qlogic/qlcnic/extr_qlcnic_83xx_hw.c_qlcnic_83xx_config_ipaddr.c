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
typedef  int u32 ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* netdev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_CONFIGURE_IP_ADDR ; 
 int QLCNIC_IP_UP ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_set_interface_id_ipaddr (struct qlcnic_adapter*,int*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int swab32 (int /*<<< orphan*/ ) ; 

void qlcnic_83xx_config_ipaddr(struct qlcnic_adapter *adapter, __be32 ip,
			       int mode)
{
	int err;
	u32 temp = 0, temp_ip;
	struct qlcnic_cmd_args cmd;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_CONFIGURE_IP_ADDR);
	if (err)
		return;

	qlcnic_83xx_set_interface_id_ipaddr(adapter, &temp);

	if (mode == QLCNIC_IP_UP)
		cmd.req.arg[1] = 1 | temp;
	else
		cmd.req.arg[1] = 2 | temp;

	/*
	 * Adapter needs IP address in network byte order.
	 * But hardware mailbox registers go through writel(), hence IP address
	 * gets swapped on big endian architecture.
	 * To negate swapping of writel() on big endian architecture
	 * use swab32(value).
	 */

	temp_ip = swab32(ntohl(ip));
	memcpy(&cmd.req.arg[2], &temp_ip, sizeof(u32));
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err != QLCNIC_RCODE_SUCCESS)
		dev_err(&adapter->netdev->dev,
			"could not notify %s IP 0x%x request\n",
			(mode == QLCNIC_IP_UP) ? "Add" : "Remove", ip);

	qlcnic_free_mbx_args(&cmd);
}