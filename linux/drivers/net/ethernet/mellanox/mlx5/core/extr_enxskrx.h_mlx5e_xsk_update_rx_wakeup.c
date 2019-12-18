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
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xsk_clear_rx_need_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_set_rx_need_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_uses_need_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mlx5e_xsk_update_rx_wakeup(struct mlx5e_rq *rq, bool alloc_err)
{
	if (!xsk_umem_uses_need_wakeup(rq->umem))
		return alloc_err;

	if (unlikely(alloc_err))
		xsk_set_rx_need_wakeup(rq->umem);
	else
		xsk_clear_rx_need_wakeup(rq->umem);

	return false;
}