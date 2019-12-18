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
struct mlx5e_xdpsq {scalar_t__ pc; scalar_t__ cc; int /*<<< orphan*/  umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsk_clear_tx_need_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_set_tx_need_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_uses_need_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5e_xsk_update_tx_wakeup(struct mlx5e_xdpsq *sq)
{
	if (!xsk_umem_uses_need_wakeup(sq->umem))
		return;

	if (sq->pc != sq->cc)
		xsk_clear_tx_need_wakeup(sq->umem);
	else
		xsk_set_tx_need_wakeup(sq->umem);
}