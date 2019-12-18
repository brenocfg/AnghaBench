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
struct mlx5_core_dev {struct device* device; } ;
struct mlx5_cmd {int /*<<< orphan*/  alloc_dma; int /*<<< orphan*/  cmd_alloc_buf; int /*<<< orphan*/  alloc_size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmd_page(struct mlx5_core_dev *dev, struct mlx5_cmd *cmd)
{
	struct device *ddev = dev->device;

	dma_free_coherent(ddev, cmd->alloc_size, cmd->cmd_alloc_buf,
			  cmd->alloc_dma);
}