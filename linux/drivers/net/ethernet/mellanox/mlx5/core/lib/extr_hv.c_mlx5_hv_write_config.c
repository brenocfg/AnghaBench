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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int mlx5_hv_config_common (struct mlx5_core_dev*,void*,int,int,int) ; 

int mlx5_hv_write_config(struct mlx5_core_dev *dev, void *buf, int len,
			 int offset)
{
	return mlx5_hv_config_common(dev, buf, len, offset, false);
}