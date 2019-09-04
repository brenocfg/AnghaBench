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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct be_vf_cfg {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  if_handle; int /*<<< orphan*/  pmac_id; } ;
struct be_adapter {int num_vfs; TYPE_1__* pdev; struct be_vf_cfg* vf_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int EINVAL ; 
 int EPERM ; 
 int be_cmd_pmac_add (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int be_cmd_set_mac (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int be_cmd_status (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sriov_enabled (struct be_adapter*) ; 

__attribute__((used)) static int be_set_vf_mac(struct net_device *netdev, int vf, u8 *mac)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	int status;

	if (!sriov_enabled(adapter))
		return -EPERM;

	if (!is_valid_ether_addr(mac) || vf >= adapter->num_vfs)
		return -EINVAL;

	/* Proceed further only if user provided MAC is different
	 * from active MAC
	 */
	if (ether_addr_equal(mac, vf_cfg->mac_addr))
		return 0;

	if (BEx_chip(adapter)) {
		be_cmd_pmac_del(adapter, vf_cfg->if_handle, vf_cfg->pmac_id,
				vf + 1);

		status = be_cmd_pmac_add(adapter, mac, vf_cfg->if_handle,
					 &vf_cfg->pmac_id, vf + 1);
	} else {
		status = be_cmd_set_mac(adapter, mac, vf_cfg->if_handle,
					vf + 1);
	}

	if (status) {
		dev_err(&adapter->pdev->dev, "MAC %pM set on VF %d Failed: %#x",
			mac, vf, status);
		return be_cmd_status(status);
	}

	ether_addr_copy(vf_cfg->mac_addr, mac);

	return 0;
}