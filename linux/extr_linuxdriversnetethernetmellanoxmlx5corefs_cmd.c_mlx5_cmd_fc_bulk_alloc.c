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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_cmd_fc_bulk {int num; int outlen; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 struct mlx5_cmd_fc_bulk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_flow_counter_out ; 
 int /*<<< orphan*/  traffic_counter ; 

struct mlx5_cmd_fc_bulk *
mlx5_cmd_fc_bulk_alloc(struct mlx5_core_dev *dev, u32 id, int num)
{
	struct mlx5_cmd_fc_bulk *b;
	int outlen =
		MLX5_ST_SZ_BYTES(query_flow_counter_out) +
		MLX5_ST_SZ_BYTES(traffic_counter) * num;

	b = kzalloc(sizeof(*b) + outlen, GFP_KERNEL);
	if (!b)
		return NULL;

	b->id = id;
	b->num = num;
	b->outlen = outlen;

	return b;
}