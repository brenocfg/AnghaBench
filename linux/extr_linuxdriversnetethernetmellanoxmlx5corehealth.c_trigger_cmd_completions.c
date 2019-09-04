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
typedef  unsigned long u64 ;
struct TYPE_2__ {unsigned long bitmask; int log_sz; int /*<<< orphan*/  alloc_lock; } ;
struct mlx5_core_dev {TYPE_1__ cmd; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_EQ_VEC_CMD ; 
 unsigned long MLX5_TRIGGERED_CMD_COMP ; 
 int /*<<< orphan*/  mlx5_cmd_comp_handler (struct mlx5_core_dev*,unsigned long,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,unsigned long) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trigger_cmd_completions(struct mlx5_core_dev *dev)
{
	unsigned long flags;
	u64 vector;

	/* wait for pending handlers to complete */
	synchronize_irq(pci_irq_vector(dev->pdev, MLX5_EQ_VEC_CMD));
	spin_lock_irqsave(&dev->cmd.alloc_lock, flags);
	vector = ~dev->cmd.bitmask & ((1ul << (1 << dev->cmd.log_sz)) - 1);
	if (!vector)
		goto no_trig;

	vector |= MLX5_TRIGGERED_CMD_COMP;
	spin_unlock_irqrestore(&dev->cmd.alloc_lock, flags);

	mlx5_core_dbg(dev, "vector 0x%llx\n", vector);
	mlx5_cmd_comp_handler(dev, vector, true);
	return;

no_trig:
	spin_unlock_irqrestore(&dev->cmd.alloc_lock, flags);
}