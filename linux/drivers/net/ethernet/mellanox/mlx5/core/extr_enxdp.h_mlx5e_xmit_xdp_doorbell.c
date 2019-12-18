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
struct mlx5e_xdpsq {int /*<<< orphan*/ * doorbell_cseg; int /*<<< orphan*/  uar_map; int /*<<< orphan*/  pc; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_notify_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mlx5e_xmit_xdp_doorbell(struct mlx5e_xdpsq *sq)
{
	if (sq->doorbell_cseg) {
		mlx5e_notify_hw(&sq->wq, sq->pc, sq->uar_map, sq->doorbell_cseg);
		sq->doorbell_cseg = NULL;
	}
}