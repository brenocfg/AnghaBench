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
typedef  int u8 ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_WIDTH_12X ; 
 int IB_WIDTH_1X ; 
 int IB_WIDTH_2X ; 
 int IB_WIDTH_4X ; 
 int IB_WIDTH_8X ; 
 int MLX5_IB_WIDTH_12X ; 
 int MLX5_IB_WIDTH_1X ; 
 int MLX5_IB_WIDTH_2X ; 
 int MLX5_IB_WIDTH_4X ; 
 int MLX5_IB_WIDTH_8X ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static void translate_active_width(struct ib_device *ibdev, u8 active_width,
				  u8 *ib_width)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);

	if (active_width & MLX5_IB_WIDTH_1X)
		*ib_width = IB_WIDTH_1X;
	else if (active_width & MLX5_IB_WIDTH_2X)
		*ib_width = IB_WIDTH_2X;
	else if (active_width & MLX5_IB_WIDTH_4X)
		*ib_width = IB_WIDTH_4X;
	else if (active_width & MLX5_IB_WIDTH_8X)
		*ib_width = IB_WIDTH_8X;
	else if (active_width & MLX5_IB_WIDTH_12X)
		*ib_width = IB_WIDTH_12X;
	else {
		mlx5_ib_dbg(dev, "Invalid active_width %d, setting width to default value: 4x\n",
			    (int)active_width);
		*ib_width = IB_WIDTH_4X;
	}

	return;
}