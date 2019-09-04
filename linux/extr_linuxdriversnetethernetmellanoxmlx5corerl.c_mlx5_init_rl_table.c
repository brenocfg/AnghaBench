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
struct mlx5_rl_table {int max_size; int max_rate; int min_rate; TYPE_2__* rl_entry; int /*<<< orphan*/  rl_lock; } ;
struct mlx5_rl_entry {int dummy; } ;
struct TYPE_3__ {struct mlx5_rl_table rl_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 void* MLX5_CAP_QOS (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_pacing ; 
 int /*<<< orphan*/  packet_pacing_max_rate ; 
 int /*<<< orphan*/  packet_pacing_min_rate ; 
 int /*<<< orphan*/  packet_pacing_rate_table_size ; 
 int /*<<< orphan*/  qos ; 

int mlx5_init_rl_table(struct mlx5_core_dev *dev)
{
	struct mlx5_rl_table *table = &dev->priv.rl_table;
	int i;

	mutex_init(&table->rl_lock);
	if (!MLX5_CAP_GEN(dev, qos) || !MLX5_CAP_QOS(dev, packet_pacing)) {
		table->max_size = 0;
		return 0;
	}

	/* First entry is reserved for unlimited rate */
	table->max_size = MLX5_CAP_QOS(dev, packet_pacing_rate_table_size) - 1;
	table->max_rate = MLX5_CAP_QOS(dev, packet_pacing_max_rate);
	table->min_rate = MLX5_CAP_QOS(dev, packet_pacing_min_rate);

	table->rl_entry = kcalloc(table->max_size, sizeof(struct mlx5_rl_entry),
				  GFP_KERNEL);
	if (!table->rl_entry)
		return -ENOMEM;

	/* The index represents the index in HW rate limit table
	 * Index 0 is reserved for unlimited rate
	 */
	for (i = 0; i < table->max_size; i++)
		table->rl_entry[i].index = i + 1;

	/* Index 0 is reserved */
	mlx5_core_info(dev, "Rate limit: %u rates are supported, range: %uMbps to %uMbps\n",
		       table->max_size,
		       table->min_rate >> 10,
		       table->max_rate >> 10);

	return 0;
}