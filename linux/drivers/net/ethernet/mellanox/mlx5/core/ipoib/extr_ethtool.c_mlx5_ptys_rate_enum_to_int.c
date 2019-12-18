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
typedef  enum mlx5_ptys_rate { ____Placeholder_mlx5_ptys_rate } mlx5_ptys_rate ;

/* Variables and functions */
#define  MLX5_PTYS_RATE_DDR 134 
#define  MLX5_PTYS_RATE_EDR 133 
#define  MLX5_PTYS_RATE_FDR 132 
#define  MLX5_PTYS_RATE_FDR10 131 
#define  MLX5_PTYS_RATE_HDR 130 
#define  MLX5_PTYS_RATE_QDR 129 
#define  MLX5_PTYS_RATE_SDR 128 

__attribute__((used)) static inline int mlx5_ptys_rate_enum_to_int(enum mlx5_ptys_rate rate)
{
	switch (rate) {
	case MLX5_PTYS_RATE_SDR:   return 2500;
	case MLX5_PTYS_RATE_DDR:   return 5000;
	case MLX5_PTYS_RATE_QDR:
	case MLX5_PTYS_RATE_FDR10: return 10000;
	case MLX5_PTYS_RATE_FDR:   return 14000;
	case MLX5_PTYS_RATE_EDR:   return 25000;
	case MLX5_PTYS_RATE_HDR:   return 50000;
	default:		   return -1;
	}
}