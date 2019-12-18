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
struct xdp_umem {scalar_t__ headroom; scalar_t__ chunk_size_nohr; } ;
struct mlx5e_xsk_param {scalar_t__ chunk_size; scalar_t__ headroom; } ;

/* Variables and functions */

void mlx5e_build_xsk_param(struct xdp_umem *umem, struct mlx5e_xsk_param *xsk)
{
	xsk->headroom = umem->headroom;
	xsk->chunk_size = umem->chunk_size_nohr + umem->headroom;
}