#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dma_fifo; int /*<<< orphan*/  wqe_info; } ;
struct mlx5e_txqsq {TYPE_1__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_free_txqsq_db(struct mlx5e_txqsq *sq)
{
	kvfree(sq->db.wqe_info);
	kvfree(sq->db.dma_fifo);
}