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
typedef  int u64 ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_LIB_CAP_4K_UAR ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,char*) ; 

__attribute__((used)) static void print_lib_caps(struct mlx5_ib_dev *dev, u64 caps)
{
	mlx5_ib_dbg(dev, "MLX5_LIB_CAP_4K_UAR = %s\n",
		    caps & MLX5_LIB_CAP_4K_UAR ? "y" : "n");
}