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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_cmd_fc_bulk {int id; int num; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET64 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * flow_statistics ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int,int) ; 
 int /*<<< orphan*/ * octets ; 
 int /*<<< orphan*/  query_flow_counter_out ; 
 int /*<<< orphan*/  traffic_counter ; 

void mlx5_cmd_fc_bulk_get(struct mlx5_core_dev *dev,
			  struct mlx5_cmd_fc_bulk *b, u32 id,
			  u64 *packets, u64 *bytes)
{
	int index = id - b->id;
	void *stats;

	if (index < 0 || index >= b->num) {
		mlx5_core_warn(dev, "Flow counter id (0x%x) out of range (0x%x..0x%x). Counter ignored.\n",
			       id, b->id, b->id + b->num - 1);
		return;
	}

	stats = MLX5_ADDR_OF(query_flow_counter_out, b->out,
			     flow_statistics[index]);
	*packets = MLX5_GET64(traffic_counter, stats, packets);
	*bytes = MLX5_GET64(traffic_counter, stats, octets);
}