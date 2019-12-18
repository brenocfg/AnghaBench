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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fc_cache {scalar_t__ packets; int /*<<< orphan*/  lastuse; scalar_t__ bytes; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_GET64 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * flow_statistics ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  octets ; 
 scalar_t__ packets ; 
 int /*<<< orphan*/  query_flow_counter_out ; 
 int /*<<< orphan*/  traffic_counter ; 

__attribute__((used)) static void update_counter_cache(int index, u32 *bulk_raw_data,
				 struct mlx5_fc_cache *cache)
{
	void *stats = MLX5_ADDR_OF(query_flow_counter_out, bulk_raw_data,
			     flow_statistics[index]);
	u64 packets = MLX5_GET64(traffic_counter, stats, packets);
	u64 bytes = MLX5_GET64(traffic_counter, stats, octets);

	if (cache->packets == packets)
		return;

	cache->packets = packets;
	cache->bytes = bytes;
	cache->lastuse = jiffies;
}