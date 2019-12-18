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
struct net_device {unsigned int num_tx_queues; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_2__ {int partition_id; } ;
struct i40e_pf {size_t lan_vsi; TYPE_1__ hw; struct i40e_vsi** vsi; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 unsigned int I40E_MAX_TRAFFIC_CLASS ; 
 unsigned int I40E_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  i40e_add_stat_strings (int /*<<< orphan*/ **,int /*<<< orphan*/ ,...) ; 
 int i40e_get_stats_count (struct net_device*) ; 
 int /*<<< orphan*/  i40e_gstrings_misc_stats ; 
 int /*<<< orphan*/  i40e_gstrings_net_stats ; 
 int /*<<< orphan*/  i40e_gstrings_pfc_stats ; 
 int /*<<< orphan*/  i40e_gstrings_queue_stats ; 
 int /*<<< orphan*/  i40e_gstrings_stats ; 
 int /*<<< orphan*/  i40e_gstrings_veb_stats ; 
 int /*<<< orphan*/  i40e_gstrings_veb_tc_stats ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40e_get_stat_strings(struct net_device *netdev, u8 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	unsigned int i;
	u8 *p = data;

	i40e_add_stat_strings(&data, i40e_gstrings_net_stats);

	i40e_add_stat_strings(&data, i40e_gstrings_misc_stats);

	for (i = 0; i < netdev->num_tx_queues; i++) {
		i40e_add_stat_strings(&data, i40e_gstrings_queue_stats,
				      "tx", i);
		i40e_add_stat_strings(&data, i40e_gstrings_queue_stats,
				      "rx", i);
	}

	if (vsi != pf->vsi[pf->lan_vsi] || pf->hw.partition_id != 1)
		goto check_data_pointer;

	i40e_add_stat_strings(&data, i40e_gstrings_veb_stats);

	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		i40e_add_stat_strings(&data, i40e_gstrings_veb_tc_stats, i);

	i40e_add_stat_strings(&data, i40e_gstrings_stats);

	for (i = 0; i < I40E_MAX_USER_PRIORITY; i++)
		i40e_add_stat_strings(&data, i40e_gstrings_pfc_stats, i);

check_data_pointer:
	WARN_ONCE(data - p != i40e_get_stats_count(netdev) * ETH_GSTRING_LEN,
		  "stat strings count mismatch!");
}