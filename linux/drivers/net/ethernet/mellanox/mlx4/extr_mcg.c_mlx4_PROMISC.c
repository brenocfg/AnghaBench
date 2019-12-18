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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_PROMISC ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int mlx4_cmd (struct mlx4_dev*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_PROMISC(struct mlx4_dev *dev, u32 qpn,
			enum mlx4_steer_type steer, u8 add, u8 port)
{
	return mlx4_cmd(dev, (u64) qpn | (u64) port << 62, (u32) steer, add,
			MLX4_CMD_PROMISC, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_WRAPPED);
}