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
struct mlx5e_params {int /*<<< orphan*/  lro_en; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ mlx5e_rx_get_linear_frag_sz (struct mlx5e_params*) ; 

__attribute__((used)) static bool mlx5e_rx_is_linear_skb(struct mlx5_core_dev *mdev,
				   struct mlx5e_params *params)
{
	u32 frag_sz = mlx5e_rx_get_linear_frag_sz(params);

	return !params->lro_en && frag_sz <= PAGE_SIZE;
}