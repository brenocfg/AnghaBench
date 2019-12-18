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
typedef  int u32 ;

/* Variables and functions */
#define  MLX5_FPGA_DEVICE_KU040 131 
#define  MLX5_FPGA_DEVICE_KU060 130 
#define  MLX5_FPGA_DEVICE_KU060_2 129 
#define  MLX5_FPGA_DEVICE_UNKNOWN 128 

__attribute__((used)) static const char *mlx5_fpga_device_name(u32 device)
{
	switch (device) {
	case MLX5_FPGA_DEVICE_KU040:
		return "ku040";
	case MLX5_FPGA_DEVICE_KU060:
		return "ku060";
	case MLX5_FPGA_DEVICE_KU060_2:
		return "ku060_2";
	case MLX5_FPGA_DEVICE_UNKNOWN:
	default:
		return "unknown";
	}
}