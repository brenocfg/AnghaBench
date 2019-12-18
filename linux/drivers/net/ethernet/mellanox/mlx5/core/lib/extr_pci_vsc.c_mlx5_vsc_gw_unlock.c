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
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VSC_UNLOCK ; 
 int /*<<< orphan*/  VSC_SEMAPHORE_OFFSET ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (int /*<<< orphan*/ ) ; 
 int vsc_write (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5_vsc_gw_unlock(struct mlx5_core_dev *dev)
{
	int ret;

	ret = vsc_write(dev, VSC_SEMAPHORE_OFFSET, MLX5_VSC_UNLOCK);
	pci_cfg_access_unlock(dev->pdev);
	return ret;
}