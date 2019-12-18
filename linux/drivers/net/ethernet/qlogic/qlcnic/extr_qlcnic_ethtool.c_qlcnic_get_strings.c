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
struct qlcnic_adapter {int drv_tx_rings; int flags; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {char* stat_string; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int QLCNIC_ESWITCH_ENABLED ; 
 int QLCNIC_STATS_LEN ; 
 int QLCNIC_TEST_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 char** qlcnic_83xx_mac_stats_strings ; 
 char** qlcnic_83xx_rx_stats_strings ; 
 char** qlcnic_83xx_tx_stats_strings ; 
 char** qlcnic_device_gstrings_stats ; 
 TYPE_1__* qlcnic_gstrings_stats ; 
 char** qlcnic_gstrings_test ; 
 char** qlcnic_tx_queue_stats_strings ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static void
qlcnic_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int index, i, num_stats;

	switch (stringset) {
	case ETH_SS_TEST:
		memcpy(data, *qlcnic_gstrings_test,
		       QLCNIC_TEST_LEN * ETH_GSTRING_LEN);
		break;
	case ETH_SS_STATS:
		num_stats = ARRAY_SIZE(qlcnic_tx_queue_stats_strings);
		for (i = 0; i < adapter->drv_tx_rings; i++) {
			for (index = 0; index < num_stats; index++) {
				sprintf(data, "tx_queue_%d %s", i,
					qlcnic_tx_queue_stats_strings[index]);
				data += ETH_GSTRING_LEN;
			}
		}

		for (index = 0; index < QLCNIC_STATS_LEN; index++) {
			memcpy(data + index * ETH_GSTRING_LEN,
			       qlcnic_gstrings_stats[index].stat_string,
			       ETH_GSTRING_LEN);
		}

		if (qlcnic_83xx_check(adapter)) {
			num_stats = ARRAY_SIZE(qlcnic_83xx_tx_stats_strings);
			for (i = 0; i < num_stats; i++, index++)
				memcpy(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_tx_stats_strings[i],
				       ETH_GSTRING_LEN);
			num_stats = ARRAY_SIZE(qlcnic_83xx_mac_stats_strings);
			for (i = 0; i < num_stats; i++, index++)
				memcpy(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_mac_stats_strings[i],
				       ETH_GSTRING_LEN);
			num_stats = ARRAY_SIZE(qlcnic_83xx_rx_stats_strings);
			for (i = 0; i < num_stats; i++, index++)
				memcpy(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_rx_stats_strings[i],
				       ETH_GSTRING_LEN);
			return;
		} else {
			num_stats = ARRAY_SIZE(qlcnic_83xx_mac_stats_strings);
			for (i = 0; i < num_stats; i++, index++)
				memcpy(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_mac_stats_strings[i],
				       ETH_GSTRING_LEN);
		}
		if (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
			return;
		num_stats = ARRAY_SIZE(qlcnic_device_gstrings_stats);
		for (i = 0; i < num_stats; index++, i++) {
			memcpy(data + index * ETH_GSTRING_LEN,
			       qlcnic_device_gstrings_stats[i],
			       ETH_GSTRING_LEN);
		}
	}
}