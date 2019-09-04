#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_8__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_12__ {TYPE_4__ ipv6_layout; TYPE_2__ ipv4_layout; } ;
struct TYPE_9__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_7__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_11__ {TYPE_3__ ipv6_layout; TYPE_1__ ipv4_layout; } ;

/* Variables and functions */
 void const* MLX5_ADDR_OF (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ dst_ipv4_dst_ipv6 ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  ipv4 ; 
 int /*<<< orphan*/  ipv4_layout ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  ipv6_layout ; 
 int /*<<< orphan*/  is_full_mask (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_parameters ; 
 scalar_t__ mlx5_fs_is_outer_ipv4_flow (struct mlx5_core_dev*,void const*,void const*) ; 
 int /*<<< orphan*/  outer_esp_spi ; 
 int /*<<< orphan*/  outer_headers ; 
 TYPE_5__ src_ipv4_src_ipv6 ; 

__attribute__((used)) static bool validate_fpga_full_mask(struct mlx5_core_dev *dev,
				    const u32 *match_c,
				    const u32 *match_v)
{
	const void *misc_params_c = MLX5_ADDR_OF(fte_match_param,
						 match_c,
						 misc_parameters);
	const void *headers_c = MLX5_ADDR_OF(fte_match_param,
					     match_c,
					     outer_headers);
	const void *headers_v = MLX5_ADDR_OF(fte_match_param,
					     match_v,
					     outer_headers);

	if (mlx5_fs_is_outer_ipv4_flow(dev, headers_c, headers_v)) {
		const void *s_ipv4_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    src_ipv4_src_ipv6.ipv4_layout.ipv4);
		const void *d_ipv4_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    dst_ipv4_dst_ipv6.ipv4_layout.ipv4);

		if (!is_full_mask(s_ipv4_c, MLX5_FLD_SZ_BYTES(ipv4_layout,
							      ipv4)) ||
		    !is_full_mask(d_ipv4_c, MLX5_FLD_SZ_BYTES(ipv4_layout,
							      ipv4)))
			return false;
	} else {
		const void *s_ipv6_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    src_ipv4_src_ipv6.ipv6_layout.ipv6);
		const void *d_ipv6_c = MLX5_ADDR_OF(fte_match_set_lyr_2_4,
						    headers_c,
						    dst_ipv4_dst_ipv6.ipv6_layout.ipv6);

		if (!is_full_mask(s_ipv6_c, MLX5_FLD_SZ_BYTES(ipv6_layout,
							      ipv6)) ||
		    !is_full_mask(d_ipv6_c, MLX5_FLD_SZ_BYTES(ipv6_layout,
							      ipv6)))
			return false;
	}

	if (!is_full_mask(MLX5_ADDR_OF(fte_match_set_misc, misc_params_c,
				       outer_esp_spi),
			  MLX5_FLD_SZ_BYTES(fte_match_set_misc, outer_esp_spi)))
		return false;

	return true;
}