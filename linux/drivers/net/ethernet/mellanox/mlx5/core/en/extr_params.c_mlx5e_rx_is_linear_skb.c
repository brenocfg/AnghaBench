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
typedef  scalar_t__ u32 ;
struct mlx5e_xsk_param {int dummy; } ;
struct mlx5e_params {int /*<<< orphan*/  lro_en; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_rx_get_linear_frag_sz (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 

bool mlx5e_rx_is_linear_skb(struct mlx5e_params *params,
			    struct mlx5e_xsk_param *xsk)
{
	/* AF_XDP allocates SKBs on XDP_PASS - ensure they don't occupy more
	 * than one page. For this, check both with and without xsk.
	 */
	u32 linear_frag_sz = max(mlx5e_rx_get_linear_frag_sz(params, xsk),
				 mlx5e_rx_get_linear_frag_sz(params, NULL));

	return !params->lro_en && linear_frag_sz <= PAGE_SIZE;
}