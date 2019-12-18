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
struct wiphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmkid_list; } ;
struct wilc_vif {TYPE_1__ priv; } ;
struct wilc_pmkid_attr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int flush_pmksa(struct wiphy *wiphy, struct net_device *netdev)
{
	struct wilc_vif *vif = netdev_priv(netdev);

	memset(&vif->priv.pmkid_list, 0, sizeof(struct wilc_pmkid_attr));

	return 0;
}