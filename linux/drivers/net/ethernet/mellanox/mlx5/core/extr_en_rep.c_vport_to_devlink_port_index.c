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
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_CAP_GEN (struct mlx5_core_dev const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhca_id ; 

__attribute__((used)) static unsigned int
vport_to_devlink_port_index(const struct mlx5_core_dev *dev, u16 vport_num)
{
	return (MLX5_CAP_GEN(dev, vhca_id) << 16) | vport_num;
}