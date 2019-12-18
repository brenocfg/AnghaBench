#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xi; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_info; TYPE_1__ xdpi_fifo; } ;
struct mlx5e_xdpsq {TYPE_2__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_free_xdpsq_db(struct mlx5e_xdpsq *sq)
{
	kvfree(sq->db.xdpi_fifo.xi);
	kvfree(sq->db.wqe_info);
}