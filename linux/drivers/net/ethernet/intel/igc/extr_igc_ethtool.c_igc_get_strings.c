#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct igc_adapter {int num_tx_queues; int num_rx_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_string; } ;
struct TYPE_3__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int IGC_GLOBAL_STATS_LEN ; 
 int IGC_NETDEV_STATS_LEN ; 
 int IGC_PRIV_FLAGS_STR_LEN ; 
 int IGC_TEST_LEN ; 
 TYPE_2__* igc_gstrings_net_stats ; 
 TYPE_1__* igc_gstrings_stats ; 
 int /*<<< orphan*/ * igc_gstrings_test ; 
 int /*<<< orphan*/  igc_priv_flags_strings ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void igc_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct igc_adapter *adapter = netdev_priv(netdev);
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_TEST:
		memcpy(data, *igc_gstrings_test,
		       IGC_TEST_LEN * ETH_GSTRING_LEN);
		break;
	case ETH_SS_STATS:
		for (i = 0; i < IGC_GLOBAL_STATS_LEN; i++) {
			memcpy(p, igc_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < IGC_NETDEV_STATS_LEN; i++) {
			memcpy(p, igc_gstrings_net_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < adapter->num_tx_queues; i++) {
			sprintf(p, "tx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_queue_%u_restart", i);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < adapter->num_rx_queues; i++) {
			sprintf(p, "rx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_drops", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_csum_err", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_alloc_failed", i);
			p += ETH_GSTRING_LEN;
		}
		/* BUG_ON(p - data != IGC_STATS_LEN * ETH_GSTRING_LEN); */
		break;
	case ETH_SS_PRIV_FLAGS:
		memcpy(data, igc_priv_flags_strings,
		       IGC_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
		break;
	}
}