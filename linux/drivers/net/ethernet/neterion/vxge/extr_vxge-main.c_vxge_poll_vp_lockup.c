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
struct vxgedev {int no_of_vpath; int /*<<< orphan*/  vp_lockup_timer; struct vxge_vpath* vpaths; int /*<<< orphan*/  vp_reset; } ;
struct TYPE_3__ {int /*<<< orphan*/  txq; } ;
struct TYPE_4__ {unsigned long prev_rx_frms; int /*<<< orphan*/  rx_frms; } ;
struct vxge_ring {int last_status; TYPE_2__ stats; int /*<<< orphan*/  handle; } ;
struct vxge_vpath {TYPE_1__ fifo; struct vxge_ring ring; } ;
struct timer_list {int dummy; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int HZ ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int VXGE_HW_FAIL ; 
 int VXGE_HW_OK ; 
 struct vxgedev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 struct vxgedev* vdev ; 
 int /*<<< orphan*/  vp_lockup_timer ; 
 int vxge_hw_vpath_check_leak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_vpath_intr_disable (struct vxgedev*,int) ; 

__attribute__((used)) static void vxge_poll_vp_lockup(struct timer_list *t)
{
	struct vxgedev *vdev = from_timer(vdev, t, vp_lockup_timer);
	enum vxge_hw_status status = VXGE_HW_OK;
	struct vxge_vpath *vpath;
	struct vxge_ring *ring;
	int i;
	unsigned long rx_frms;

	for (i = 0; i < vdev->no_of_vpath; i++) {
		ring = &vdev->vpaths[i].ring;

		/* Truncated to machine word size number of frames */
		rx_frms = READ_ONCE(ring->stats.rx_frms);

		/* Did this vpath received any packets */
		if (ring->stats.prev_rx_frms == rx_frms) {
			status = vxge_hw_vpath_check_leak(ring->handle);

			/* Did it received any packets last time */
			if ((VXGE_HW_FAIL == status) &&
				(VXGE_HW_FAIL == ring->last_status)) {

				/* schedule vpath reset */
				if (!test_and_set_bit(i, &vdev->vp_reset)) {
					vpath = &vdev->vpaths[i];

					/* disable interrupts for this vpath */
					vxge_vpath_intr_disable(vdev, i);

					/* stop the queue for this vpath */
					netif_tx_stop_queue(vpath->fifo.txq);
					continue;
				}
			}
		}
		ring->stats.prev_rx_frms = rx_frms;
		ring->last_status = status;
	}

	/* Check every 1 milli second */
	mod_timer(&vdev->vp_lockup_timer, jiffies + HZ / 1000);
}