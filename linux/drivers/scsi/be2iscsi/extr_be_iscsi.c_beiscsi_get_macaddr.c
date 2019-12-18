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
struct beiscsi_hba {int mac_addr_set; int /*<<< orphan*/  mac_address; } ;
struct be_cmd_get_nic_conf_resp {int /*<<< orphan*/  mac_address; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_nic_conf_resp*,int /*<<< orphan*/ ,int) ; 
 int mgmt_get_nic_conf (struct beiscsi_hba*,struct be_cmd_get_nic_conf_resp*) ; 
 int sysfs_format_mac (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int beiscsi_get_macaddr(char *buf, struct beiscsi_hba *phba)
{
	struct be_cmd_get_nic_conf_resp resp;
	int rc;

	if (phba->mac_addr_set)
		return sysfs_format_mac(buf, phba->mac_address, ETH_ALEN);

	memset(&resp, 0, sizeof(resp));
	rc = mgmt_get_nic_conf(phba, &resp);
	if (rc)
		return rc;

	phba->mac_addr_set = true;
	memcpy(phba->mac_address, resp.mac_address, ETH_ALEN);
	return sysfs_format_mac(buf, phba->mac_address, ETH_ALEN);
}