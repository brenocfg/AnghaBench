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
struct mlx5_hv_vhca_data_block {int /*<<< orphan*/  member_0; } ;
struct mlx5_hv_vhca_agent {int type; TYPE_1__* hv_vhca; } ;
typedef  int /*<<< orphan*/  data_block ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HV_CONFIG_BLOCK_SIZE_MAX ; 
 int /*<<< orphan*/  mlx5_hv_vhca_agent_seq_update (struct mlx5_hv_vhca_agent*) ; 
 int mlx5_hv_vhca_data_block_prepare (struct mlx5_hv_vhca_agent*,struct mlx5_hv_vhca_data_block*,void*,int,int*) ; 
 int mlx5_hv_write_config (int /*<<< orphan*/ ,struct mlx5_hv_vhca_data_block*,int,int) ; 

int mlx5_hv_vhca_agent_write(struct mlx5_hv_vhca_agent *agent,
			     void *buf, int len)
{
	int offset = agent->type * HV_CONFIG_BLOCK_SIZE_MAX;
	int block_offset = 0;
	int total = 0;
	int err;

	while (len) {
		struct mlx5_hv_vhca_data_block data_block = {0};
		int bytes;

		bytes = mlx5_hv_vhca_data_block_prepare(agent, &data_block,
							buf + total,
							len, &block_offset);
		if (!bytes)
			return -ENOMEM;

		err = mlx5_hv_write_config(agent->hv_vhca->dev, &data_block,
					   sizeof(data_block), offset);
		if (err)
			return err;

		total += bytes;
		len   -= bytes;
	}

	mlx5_hv_vhca_agent_seq_update(agent);

	return 0;
}