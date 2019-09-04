#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bnxt {int cp_nr_rings; int flags; int num_tests; int /*<<< orphan*/  dev; TYPE_1__* test_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  string; } ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int BNXT_FLAG_PORT_STATS ; 
 int BNXT_FLAG_PORT_STATS_EXT ; 
 int BNXT_NUM_PORT_STATS ; 
 int BNXT_NUM_PORT_STATS_EXT ; 
 int BNXT_NUM_SW_FUNC_STATS ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 TYPE_4__* bnxt_port_stats_arr ; 
 TYPE_3__* bnxt_port_stats_ext_arr ; 
 TYPE_2__* bnxt_sw_func_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
{
	struct bnxt *bp = netdev_priv(dev);
	u32 i;

	switch (stringset) {
	/* The number of strings must match BNXT_NUM_STATS defined above. */
	case ETH_SS_STATS:
		for (i = 0; i < bp->cp_nr_rings; i++) {
			sprintf(buf, "[%d]: rx_ucast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_mcast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_bcast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_discards", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_drops", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_ucast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_mcast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_bcast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_ucast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_mcast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_bcast_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_discards", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_drops", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_ucast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_mcast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tx_bcast_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tpa_packets", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tpa_bytes", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tpa_events", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: tpa_aborts", i);
			buf += ETH_GSTRING_LEN;
			sprintf(buf, "[%d]: rx_l4_csum_errors", i);
			buf += ETH_GSTRING_LEN;
		}
		for (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++) {
			strcpy(buf, bnxt_sw_func_stats[i].string);
			buf += ETH_GSTRING_LEN;
		}

		if (bp->flags & BNXT_FLAG_PORT_STATS) {
			for (i = 0; i < BNXT_NUM_PORT_STATS; i++) {
				strcpy(buf, bnxt_port_stats_arr[i].string);
				buf += ETH_GSTRING_LEN;
			}
		}
		if (bp->flags & BNXT_FLAG_PORT_STATS_EXT) {
			for (i = 0; i < BNXT_NUM_PORT_STATS_EXT; i++) {
				strcpy(buf, bnxt_port_stats_ext_arr[i].string);
				buf += ETH_GSTRING_LEN;
			}
		}
		break;
	case ETH_SS_TEST:
		if (bp->num_tests)
			memcpy(buf, bp->test_info->string,
			       bp->num_tests * ETH_GSTRING_LEN);
		break;
	default:
		netdev_err(bp->dev, "bnxt_get_strings invalid request %x\n",
			   stringset);
		break;
	}
}