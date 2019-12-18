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
typedef  scalar_t__ u16 ;
struct mlx5e_xsk {scalar_t__ refcnt; } ;
struct mlx5e_params {scalar_t__ num_channels; } ;

/* Variables and functions */
 scalar_t__ mlx5e_xsk_get_umem (struct mlx5e_params*,struct mlx5e_xsk*,scalar_t__) ; 

u16 mlx5e_xsk_first_unused_channel(struct mlx5e_params *params, struct mlx5e_xsk *xsk)
{
	u16 res = xsk->refcnt ? params->num_channels : 0;

	while (res) {
		if (mlx5e_xsk_get_umem(params, xsk, res - 1))
			break;
		--res;
	}

	return res;
}