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
struct net_device {int priv_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IFF_BONDING ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static struct net_device *cxgbit_get_real_dev(struct net_device *ndev)
{
	if (ndev->priv_flags & IFF_BONDING) {
		pr_err("Bond devices are not supported. Interface:%s\n",
		       ndev->name);
		return NULL;
	}

	if (is_vlan_dev(ndev))
		return vlan_dev_real_dev(ndev);

	return ndev;
}