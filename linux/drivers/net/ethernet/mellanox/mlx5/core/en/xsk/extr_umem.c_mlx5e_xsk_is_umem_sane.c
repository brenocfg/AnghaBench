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
struct xdp_umem {int headroom; int chunk_size_nohr; } ;

/* Variables and functions */

__attribute__((used)) static bool mlx5e_xsk_is_umem_sane(struct xdp_umem *umem)
{
	return umem->headroom <= 0xffff && umem->chunk_size_nohr <= 0xffff;
}