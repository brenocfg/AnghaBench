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
struct TYPE_2__ {int max_tc_eth; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_TC_MAX_NUMBER ; 

int mlx4_max_tc(struct mlx4_dev *dev)
{
	u8 num_tc = dev->caps.max_tc_eth;

	if (!num_tc)
		num_tc = MLX4_TC_MAX_NUMBER;

	return num_tc;
}