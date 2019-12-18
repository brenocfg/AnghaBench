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
struct mlx5e_xsk {int /*<<< orphan*/ ** umems; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_xsk_put_umems (struct mlx5e_xsk*) ; 

__attribute__((used)) static void mlx5e_xsk_remove_umem(struct mlx5e_xsk *xsk, u16 ix)
{
	xsk->umems[ix] = NULL;

	mlx5e_xsk_put_umems(xsk);
}