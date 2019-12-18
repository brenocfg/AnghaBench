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
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct mlx5e_xsk {struct xdp_umem** umems; } ;
struct mlx5e_params {size_t num_channels; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct xdp_umem *mlx5e_xsk_get_umem(struct mlx5e_params *params,
						  struct mlx5e_xsk *xsk, u16 ix)
{
	if (!xsk || !xsk->umems)
		return NULL;

	if (unlikely(ix >= params->num_channels))
		return NULL;

	return xsk->umems[ix];
}