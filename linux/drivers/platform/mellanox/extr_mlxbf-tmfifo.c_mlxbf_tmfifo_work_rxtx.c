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
struct mlxbf_tmfifo_vring {scalar_t__ vq; } ;
struct mlxbf_tmfifo_vdev {struct mlxbf_tmfifo_vring* vrings; } ;
struct mlxbf_tmfifo {struct mlxbf_tmfifo_vdev** vdev; TYPE_1__* irq_info; int /*<<< orphan*/  pend_events; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int MLXBF_TMFIFO_VDEV_MAX ; 
 int /*<<< orphan*/  mlxbf_tmfifo_rxtx (struct mlxbf_tmfifo_vring*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxbf_tmfifo_work_rxtx(struct mlxbf_tmfifo *fifo, int queue_id,
				   int irq_id, bool is_rx)
{
	struct mlxbf_tmfifo_vdev *tm_vdev;
	struct mlxbf_tmfifo_vring *vring;
	int i;

	if (!test_and_clear_bit(irq_id, &fifo->pend_events) ||
	    !fifo->irq_info[irq_id].irq)
		return;

	for (i = 0; i < MLXBF_TMFIFO_VDEV_MAX; i++) {
		tm_vdev = fifo->vdev[i];
		if (tm_vdev) {
			vring = &tm_vdev->vrings[queue_id];
			if (vring->vq)
				mlxbf_tmfifo_rxtx(vring, is_rx);
		}
	}
}