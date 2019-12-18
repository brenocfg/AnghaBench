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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wilc_set_wep_default_keyid (struct wilc_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_default_key(struct wiphy *wiphy, struct net_device *netdev,
			   u8 key_index, bool unicast, bool multicast)
{
	struct wilc_vif *vif = netdev_priv(netdev);

	wilc_set_wep_default_keyid(vif, key_index);

	return 0;
}