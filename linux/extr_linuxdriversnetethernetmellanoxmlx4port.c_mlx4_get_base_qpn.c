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
typedef  int u8 ;
struct TYPE_2__ {int* reserved_qps_base; int log_num_macs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 size_t MLX4_QP_REGION_ETH_ADDR ; 

int mlx4_get_base_qpn(struct mlx4_dev *dev, u8 port)
{
	return dev->caps.reserved_qps_base[MLX4_QP_REGION_ETH_ADDR] +
			(port - 1) * (1 << dev->caps.log_num_macs);
}