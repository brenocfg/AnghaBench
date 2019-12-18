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
struct virtqueue {struct mlxbf_tmfifo_vring* priv; } ;
struct mlxbf_tmfifo_vring {int index; size_t vdev_id; struct mlxbf_tmfifo* fifo; } ;
struct mlxbf_tmfifo_vdev {int dummy; } ;
struct mlxbf_tmfifo {int /*<<< orphan*/  work; int /*<<< orphan*/  pend_events; int /*<<< orphan*/  spin_lock; struct mlxbf_tmfifo_vdev** vdev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXBF_TM_RX_HWM_IRQ ; 
 int /*<<< orphan*/  MLXBF_TM_TX_LWM_IRQ ; 
 size_t VIRTIO_ID_CONSOLE ; 
 int /*<<< orphan*/  mlxbf_tmfifo_console_output (struct mlxbf_tmfifo_vdev*,struct mlxbf_tmfifo_vring*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxbf_tmfifo_virtio_notify(struct virtqueue *vq)
{
	struct mlxbf_tmfifo_vring *vring = vq->priv;
	struct mlxbf_tmfifo_vdev *tm_vdev;
	struct mlxbf_tmfifo *fifo;
	unsigned long flags;

	fifo = vring->fifo;

	/*
	 * Virtio maintains vrings in pairs, even number ring for Rx
	 * and odd number ring for Tx.
	 */
	if (vring->index & BIT(0)) {
		/*
		 * Console could make blocking call with interrupts disabled.
		 * In such case, the vring needs to be served right away. For
		 * other cases, just set the TX LWM bit to start Tx in the
		 * worker handler.
		 */
		if (vring->vdev_id == VIRTIO_ID_CONSOLE) {
			spin_lock_irqsave(&fifo->spin_lock, flags);
			tm_vdev = fifo->vdev[VIRTIO_ID_CONSOLE];
			mlxbf_tmfifo_console_output(tm_vdev, vring);
			spin_unlock_irqrestore(&fifo->spin_lock, flags);
		} else if (test_and_set_bit(MLXBF_TM_TX_LWM_IRQ,
					    &fifo->pend_events)) {
			return true;
		}
	} else {
		if (test_and_set_bit(MLXBF_TM_RX_HWM_IRQ, &fifo->pend_events))
			return true;
	}

	schedule_work(&fifo->work);

	return true;
}