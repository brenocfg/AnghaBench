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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct netcp_intf {int dummy; } ;
struct net_device {int dummy; } ;
struct gbe_priv {int num_et_stats; TYPE_1__* et_stats; } ;
struct gbe_intf {struct gbe_priv* gbe_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 struct gbe_intf* keystone_get_intf_data (struct netcp_intf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void keystone_get_stat_strings(struct net_device *ndev,
				      uint32_t stringset, uint8_t *data)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct gbe_intf *gbe_intf;
	struct gbe_priv *gbe_dev;
	int i;

	gbe_intf = keystone_get_intf_data(netcp);
	if (!gbe_intf)
		return;
	gbe_dev = gbe_intf->gbe_dev;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < gbe_dev->num_et_stats; i++) {
			memcpy(data, gbe_dev->et_stats[i].desc,
			       ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		}
		break;
	case ETH_SS_TEST:
		break;
	}
}