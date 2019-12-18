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
struct mlxbf_tmfifo {int is_ready; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int MLXBF_TMFIFO_VDEV_MAX ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_delete_vdev (struct mlxbf_tmfifo*,int) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_disable_irqs (struct mlxbf_tmfifo*) ; 

__attribute__((used)) static void mlxbf_tmfifo_cleanup(struct mlxbf_tmfifo *fifo)
{
	int i;

	fifo->is_ready = false;
	del_timer_sync(&fifo->timer);
	mlxbf_tmfifo_disable_irqs(fifo);
	cancel_work_sync(&fifo->work);
	for (i = 0; i < MLXBF_TMFIFO_VDEV_MAX; i++)
		mlxbf_tmfifo_delete_vdev(fifo, i);
}