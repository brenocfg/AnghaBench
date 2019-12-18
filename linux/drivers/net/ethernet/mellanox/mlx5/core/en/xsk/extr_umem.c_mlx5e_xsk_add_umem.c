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

/* Variables and functions */
 int mlx5e_xsk_get_umems (struct mlx5e_xsk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_xsk_add_umem(struct mlx5e_xsk *xsk, struct xdp_umem *umem, u16 ix)
{
	int err;

	err = mlx5e_xsk_get_umems(xsk);
	if (unlikely(err))
		return err;

	xsk->umems[ix] = umem;
	return 0;
}