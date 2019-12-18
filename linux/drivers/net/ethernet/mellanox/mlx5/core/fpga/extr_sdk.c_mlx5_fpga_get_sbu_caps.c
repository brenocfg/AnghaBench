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
struct mlx5_fpga_device {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_fpga_sbu_caps (int /*<<< orphan*/ ,void*,int) ; 

int mlx5_fpga_get_sbu_caps(struct mlx5_fpga_device *fdev, int size, void *buf)
{
	return mlx5_fpga_sbu_caps(fdev->mdev, buf, size);
}