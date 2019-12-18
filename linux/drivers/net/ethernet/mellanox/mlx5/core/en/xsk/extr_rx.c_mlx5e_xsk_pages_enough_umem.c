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
struct mlx5e_rq {int /*<<< orphan*/  umem; } ;

/* Variables and functions */
 int xsk_umem_has_addrs_rq (int /*<<< orphan*/ ,int) ; 

bool mlx5e_xsk_pages_enough_umem(struct mlx5e_rq *rq, int count)
{
	/* Check in advance that we have enough frames, instead of allocating
	 * one-by-one, failing and moving frames to the Reuse Ring.
	 */
	return xsk_umem_has_addrs_rq(rq->umem, count);
}