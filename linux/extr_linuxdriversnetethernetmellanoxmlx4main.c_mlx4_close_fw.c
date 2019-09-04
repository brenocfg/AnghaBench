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
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_icm; } ;
struct TYPE_4__ {TYPE_1__ fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_UNMAP_FA (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

__attribute__((used)) static void mlx4_close_fw(struct mlx4_dev *dev)
{
	if (!mlx4_is_slave(dev)) {
		mlx4_UNMAP_FA(dev);
		mlx4_free_icm(dev, mlx4_priv(dev)->fw.fw_icm, 0);
	}
}