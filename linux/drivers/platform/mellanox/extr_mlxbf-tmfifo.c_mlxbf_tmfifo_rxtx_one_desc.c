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
typedef  scalar_t__ u32 ;
struct vring_desc {int /*<<< orphan*/  next; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; } ;
struct vring {struct vring_desc* desc; } ;
struct virtio_device {int dummy; } ;
struct mlxbf_tmfifo_vring {size_t vdev_id; scalar_t__ pkt_len; scalar_t__ rem_len; scalar_t__ cur_len; struct vring_desc* desc; int /*<<< orphan*/  vq; struct mlxbf_tmfifo* fifo; } ;
struct mlxbf_tmfifo {int /*<<< orphan*/  spin_lock; int /*<<< orphan*/ ** vring; TYPE_1__** vdev; } ;
struct TYPE_2__ {struct virtio_device vdev; } ;

/* Variables and functions */
 scalar_t__ VRING_DESC_F_NEXT ; 
 struct vring_desc* mlxbf_tmfifo_get_next_pkt (struct mlxbf_tmfifo_vring*,int) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_release_pending_pkt (struct mlxbf_tmfifo_vring*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_rxtx_header (struct mlxbf_tmfifo_vring*,struct vring_desc*,int,int*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_rxtx_word (struct mlxbf_tmfifo_vring*,struct vring_desc*,int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ virtio16_to_cpu (struct virtio_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ virtio32_to_cpu (struct virtio_device*,int /*<<< orphan*/ ) ; 
 struct vring* virtqueue_get_vring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlxbf_tmfifo_rxtx_one_desc(struct mlxbf_tmfifo_vring *vring,
				       bool is_rx, int *avail)
{
	const struct vring *vr = virtqueue_get_vring(vring->vq);
	struct mlxbf_tmfifo *fifo = vring->fifo;
	struct virtio_device *vdev;
	bool vring_change = false;
	struct vring_desc *desc;
	unsigned long flags;
	u32 len, idx;

	vdev = &fifo->vdev[vring->vdev_id]->vdev;

	/* Get the descriptor of the next packet. */
	if (!vring->desc) {
		desc = mlxbf_tmfifo_get_next_pkt(vring, is_rx);
		if (!desc)
			return false;
	} else {
		desc = vring->desc;
	}

	/* Beginning of a packet. Start to Rx/Tx packet header. */
	if (vring->pkt_len == 0) {
		mlxbf_tmfifo_rxtx_header(vring, desc, is_rx, &vring_change);
		(*avail)--;

		/* Return if new packet is for another ring. */
		if (vring_change)
			return false;
		goto mlxbf_tmfifo_desc_done;
	}

	/* Get the length of this desc. */
	len = virtio32_to_cpu(vdev, desc->len);
	if (len > vring->rem_len)
		len = vring->rem_len;

	/* Rx/Tx one word (8 bytes) if not done. */
	if (vring->cur_len < len) {
		mlxbf_tmfifo_rxtx_word(vring, desc, is_rx, len);
		(*avail)--;
	}

	/* Check again whether it's done. */
	if (vring->cur_len == len) {
		vring->cur_len = 0;
		vring->rem_len -= len;

		/* Get the next desc on the chain. */
		if (vring->rem_len > 0 &&
		    (virtio16_to_cpu(vdev, desc->flags) & VRING_DESC_F_NEXT)) {
			idx = virtio16_to_cpu(vdev, desc->next);
			desc = &vr->desc[idx];
			goto mlxbf_tmfifo_desc_done;
		}

		/* Done and release the pending packet. */
		mlxbf_tmfifo_release_pending_pkt(vring);
		desc = NULL;
		fifo->vring[is_rx] = NULL;

		/* Notify upper layer that packet is done. */
		spin_lock_irqsave(&fifo->spin_lock, flags);
		vring_interrupt(0, vring->vq);
		spin_unlock_irqrestore(&fifo->spin_lock, flags);
	}

mlxbf_tmfifo_desc_done:
	/* Save the current desc. */
	vring->desc = desc;

	return true;
}