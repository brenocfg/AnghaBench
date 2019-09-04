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
typedef  enum mlx5_ptys_width { ____Placeholder_mlx5_ptys_width } mlx5_ptys_width ;

/* Variables and functions */
#define  MLX5_PTYS_WIDTH_12X 132 
#define  MLX5_PTYS_WIDTH_1X 131 
#define  MLX5_PTYS_WIDTH_2X 130 
#define  MLX5_PTYS_WIDTH_4X 129 
#define  MLX5_PTYS_WIDTH_8X 128 

__attribute__((used)) static inline int mlx5_ptys_width_enum_to_int(enum mlx5_ptys_width width)
{
	switch (width) {
	case MLX5_PTYS_WIDTH_1X:  return  1;
	case MLX5_PTYS_WIDTH_2X:  return  2;
	case MLX5_PTYS_WIDTH_4X:  return  4;
	case MLX5_PTYS_WIDTH_8X:  return  8;
	case MLX5_PTYS_WIDTH_12X: return 12;
	default:		  return -1;
	}
}