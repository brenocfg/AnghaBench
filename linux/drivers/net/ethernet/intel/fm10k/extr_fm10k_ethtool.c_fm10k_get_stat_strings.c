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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; unsigned int max_queues; } ;
struct TYPE_3__ {TYPE_2__ mac; } ;
struct fm10k_intfc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_add_stat_strings (int /*<<< orphan*/ **,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fm10k_gstrings_global_stats ; 
 int /*<<< orphan*/  fm10k_gstrings_mbx_stats ; 
 int /*<<< orphan*/  fm10k_gstrings_net_stats ; 
 int /*<<< orphan*/  fm10k_gstrings_pf_stats ; 
 int /*<<< orphan*/  fm10k_gstrings_queue_stats ; 
 scalar_t__ fm10k_mac_vf ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_get_stat_strings(struct net_device *dev, u8 *data)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	unsigned int i;

	fm10k_add_stat_strings(&data, fm10k_gstrings_net_stats);

	fm10k_add_stat_strings(&data, fm10k_gstrings_global_stats);

	fm10k_add_stat_strings(&data, fm10k_gstrings_mbx_stats);

	if (interface->hw.mac.type != fm10k_mac_vf)
		fm10k_add_stat_strings(&data, fm10k_gstrings_pf_stats);

	for (i = 0; i < interface->hw.mac.max_queues; i++) {
		fm10k_add_stat_strings(&data, fm10k_gstrings_queue_stats,
				       "tx", i);

		fm10k_add_stat_strings(&data, fm10k_gstrings_queue_stats,
				       "rx", i);
	}
}