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

/* Variables and functions */
#define  MLX5_CAP_UMR_FENCE_NONE 129 
#define  MLX5_CAP_UMR_FENCE_SMALL 128 
 int MLX5_FENCE_MODE_INITIATOR_SMALL ; 
 int MLX5_FENCE_MODE_NONE ; 
 int MLX5_FENCE_MODE_STRONG_ORDERING ; 

__attribute__((used)) static u8 mlx5_get_umr_fence(u8 umr_fence_cap)
{
	switch (umr_fence_cap) {
	case MLX5_CAP_UMR_FENCE_NONE:
		return MLX5_FENCE_MODE_NONE;
	case MLX5_CAP_UMR_FENCE_SMALL:
		return MLX5_FENCE_MODE_INITIATOR_SMALL;
	default:
		return MLX5_FENCE_MODE_STRONG_ORDERING;
	}
}