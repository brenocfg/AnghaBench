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
struct wiphy {int dummy; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send_del_key (struct qtnf_vif*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int qtnf_del_key(struct wiphy *wiphy, struct net_device *dev,
			u8 key_index, bool pairwise, const u8 *mac_addr)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	ret = qtnf_cmd_send_del_key(vif, key_index, pairwise, mac_addr);
	if (ret) {
		if (ret == -ENOENT) {
			pr_debug("VIF%u.%u: key index %d out of bounds\n",
				 vif->mac->macid, vif->vifid, key_index);
		} else {
			pr_err("VIF%u.%u: failed to delete key: idx=%u pw=%u\n",
			       vif->mac->macid, vif->vifid,
			       key_index, pairwise);
		}
	}

	return ret;
}