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
struct sockaddr {unsigned char* sa_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_4addr; int /*<<< orphan*/  iftype; } ;
struct qtnf_vif {TYPE_1__ wdev; int /*<<< orphan*/  mac; } ;
struct net_device {unsigned char* dev_addr; } ;
typedef  int /*<<< orphan*/  old_addr ;

/* Variables and functions */
 int ETH_ALEN ; 
 int eth_mac_addr (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int qtnf_cmd_send_change_intf_type (struct qtnf_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_scan_done (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qtnf_netdev_set_mac_address(struct net_device *ndev, void *addr)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct sockaddr *sa = addr;
	int ret;
	unsigned char old_addr[ETH_ALEN];

	memcpy(old_addr, sa->sa_data, sizeof(old_addr));

	ret = eth_mac_addr(ndev, sa);
	if (ret)
		return ret;

	qtnf_scan_done(vif->mac, true);

	ret = qtnf_cmd_send_change_intf_type(vif, vif->wdev.iftype,
					     vif->wdev.use_4addr,
					     sa->sa_data);

	if (ret)
		memcpy(ndev->dev_addr, old_addr, ETH_ALEN);

	return ret;
}