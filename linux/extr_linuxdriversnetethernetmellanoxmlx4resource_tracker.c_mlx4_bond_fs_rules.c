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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int mlx4_mirror_fs_rules (struct mlx4_dev*,int) ; 

int mlx4_bond_fs_rules(struct mlx4_dev *dev)
{
	return mlx4_mirror_fs_rules(dev, true);
}