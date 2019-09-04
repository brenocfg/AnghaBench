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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ena_stats {scalar_t__ stat_offset; } ;
struct ena_adapter {TYPE_1__* ena_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats; } ;
struct TYPE_3__ {TYPE_2__ admin_queue; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_ENA_COM ; 
 struct ena_stats* ena_stats_ena_com_strings ; 

__attribute__((used)) static void ena_dev_admin_queue_stats(struct ena_adapter *adapter, u64 **data)
{
	const struct ena_stats *ena_stats;
	u32 *ptr;
	int i;

	for (i = 0; i < ENA_STATS_ARRAY_ENA_COM; i++) {
		ena_stats = &ena_stats_ena_com_strings[i];

		ptr = (u32 *)((uintptr_t)&adapter->ena_dev->admin_queue.stats +
			(uintptr_t)ena_stats->stat_offset);

		*(*data)++ = *ptr;
	}
}