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
struct mlx5e_txqsq {scalar_t__ cc; scalar_t__ pc; scalar_t__ dma_fifo_cc; int /*<<< orphan*/  sqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mlx5e_reset_txqsq_cc_pc(struct mlx5e_txqsq *sq)
{
	WARN_ONCE(sq->cc != sq->pc,
		  "SQ 0x%x: cc (0x%x) != pc (0x%x)\n",
		  sq->sqn, sq->cc, sq->pc);
	sq->cc = 0;
	sq->dma_fifo_cc = 0;
	sq->pc = 0;
}