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
struct mlx5_hv_vhca_control_block {int capabilities; int control; int /*<<< orphan*/  command; int /*<<< orphan*/  command_ack; } ;
struct mlx5_hv_vhca_agent {struct mlx5_hv_vhca* hv_vhca; } ;
struct mlx5_hv_vhca {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_hv_vhca_control_block*) ; 
 struct mlx5_hv_vhca_control_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_hv_vhca_control_block*,int /*<<< orphan*/ ,int) ; 
 int mlx5_hv_read_config (struct mlx5_core_dev*,struct mlx5_hv_vhca_control_block*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_agents_control (struct mlx5_hv_vhca*,struct mlx5_hv_vhca_control_block*) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_capabilities (struct mlx5_hv_vhca*,int*) ; 
 int /*<<< orphan*/  mlx5_hv_write_config (struct mlx5_core_dev*,struct mlx5_hv_vhca_control_block*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5_hv_vhca_control_agent_invalidate(struct mlx5_hv_vhca_agent *agent,
				      u64 block_mask)
{
	struct mlx5_hv_vhca *hv_vhca = agent->hv_vhca;
	struct mlx5_core_dev *dev = hv_vhca->dev;
	struct mlx5_hv_vhca_control_block *block;
	u32 capabilities = 0;
	int err;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return;

	err = mlx5_hv_read_config(dev, block, sizeof(*block), 0);
	if (err)
		goto free_block;

	mlx5_hv_vhca_capabilities(hv_vhca, &capabilities);

	/* In case no capabilities, send empty block in return */
	if (!capabilities) {
		memset(block, 0, sizeof(*block));
		goto write;
	}

	if (block->capabilities != capabilities)
		block->capabilities = capabilities;

	if (block->control & ~capabilities)
		goto free_block;

	mlx5_hv_vhca_agents_control(hv_vhca, block);
	block->command_ack = block->command;

write:
	mlx5_hv_write_config(dev, block, sizeof(*block), 0);

free_block:
	kfree(block);
}