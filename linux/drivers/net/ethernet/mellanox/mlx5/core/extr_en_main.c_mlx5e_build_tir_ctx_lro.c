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
struct mlx5e_params {int lro_timeout; int /*<<< orphan*/  lro_en; } ;

/* Variables and functions */
 int MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_TIRC_LRO_ENABLE_MASK_IPV4_LRO ; 
 int MLX5_TIRC_LRO_ENABLE_MASK_IPV6_LRO ; 
 int ROUGH_MAX_L2_L3_HDR_SZ ; 
 int /*<<< orphan*/  lro_enable_mask ; 
 int /*<<< orphan*/  lro_max_ip_payload_size ; 
 int /*<<< orphan*/  lro_timeout_period_usecs ; 

__attribute__((used)) static void mlx5e_build_tir_ctx_lro(struct mlx5e_params *params, void *tirc)
{
	if (!params->lro_en)
		return;

#define ROUGH_MAX_L2_L3_HDR_SZ 256

	MLX5_SET(tirc, tirc, lro_enable_mask,
		 MLX5_TIRC_LRO_ENABLE_MASK_IPV4_LRO |
		 MLX5_TIRC_LRO_ENABLE_MASK_IPV6_LRO);
	MLX5_SET(tirc, tirc, lro_max_ip_payload_size,
		 (MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ - ROUGH_MAX_L2_L3_HDR_SZ) >> 8);
	MLX5_SET(tirc, tirc, lro_timeout_period_usecs, params->lro_timeout);
}