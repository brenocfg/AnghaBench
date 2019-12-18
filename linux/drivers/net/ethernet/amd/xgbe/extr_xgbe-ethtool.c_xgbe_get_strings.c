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
typedef  int u32 ;
struct xgbe_prv_data {int tx_ring_count; int rx_ring_count; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int XGBE_STATS_COUNT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* xgbe_gstring_stats ; 

__attribute__((used)) static void xgbe_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < XGBE_STATS_COUNT; i++) {
			memcpy(data, xgbe_gstring_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		}
		for (i = 0; i < pdata->tx_ring_count; i++) {
			sprintf(data, "txq_%u_packets", i);
			data += ETH_GSTRING_LEN;
			sprintf(data, "txq_%u_bytes", i);
			data += ETH_GSTRING_LEN;
		}
		for (i = 0; i < pdata->rx_ring_count; i++) {
			sprintf(data, "rxq_%u_packets", i);
			data += ETH_GSTRING_LEN;
			sprintf(data, "rxq_%u_bytes", i);
			data += ETH_GSTRING_LEN;
		}
		break;
	}
}