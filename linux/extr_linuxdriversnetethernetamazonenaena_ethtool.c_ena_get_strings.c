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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ena_stats {int /*<<< orphan*/  name; } ;
struct ena_adapter {int dummy; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_GLOBAL ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  ena_com_dev_strings (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ena_queue_strings (struct ena_adapter*,int /*<<< orphan*/ **) ; 
 struct ena_stats* ena_stats_global_strings ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ena_get_strings(struct net_device *netdev, u32 sset, u8 *data)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	const struct ena_stats *ena_stats;
	int i;

	if (sset != ETH_SS_STATS)
		return;

	for (i = 0; i < ENA_STATS_ARRAY_GLOBAL; i++) {
		ena_stats = &ena_stats_global_strings[i];

		memcpy(data, ena_stats->name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	}

	ena_queue_strings(adapter, &data);
	ena_com_dev_strings(&data);
}