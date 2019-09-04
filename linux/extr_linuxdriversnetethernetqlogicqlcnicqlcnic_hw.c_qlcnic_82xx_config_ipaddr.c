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
typedef  int u64 ;
struct qlcnic_nic_req {void** words; void* req_hdr; void* qhdr; } ;
struct qlcnic_ipaddr {int /*<<< orphan*/  ipv4; } ;
struct qlcnic_adapter {TYPE_1__* netdev; scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QLCNIC_H2C_OPCODE_CONFIG_IPADDR ; 
 int QLCNIC_HOST_REQUEST ; 
 int QLCNIC_IP_UP ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_send_cmd_descs (struct qlcnic_adapter*,struct cmd_desc_type0*,int) ; 

void qlcnic_82xx_config_ipaddr(struct qlcnic_adapter *adapter,
			       __be32 ip, int cmd)
{
	struct qlcnic_nic_req req;
	struct qlcnic_ipaddr *ipa;
	u64 word;
	int rv;

	memset(&req, 0, sizeof(struct qlcnic_nic_req));
	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	word = QLCNIC_H2C_OPCODE_CONFIG_IPADDR | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(cmd);
	ipa = (struct qlcnic_ipaddr *)&req.words[1];
	ipa->ipv4 = ip;

	rv = qlcnic_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
	if (rv != 0)
		dev_err(&adapter->netdev->dev,
				"could not notify %s IP 0x%x request\n",
				(cmd == QLCNIC_IP_UP) ? "Add" : "Remove", ip);
}