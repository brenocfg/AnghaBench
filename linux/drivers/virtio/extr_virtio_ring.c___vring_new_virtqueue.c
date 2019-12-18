#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {void (* callback ) (struct virtqueue*) ;char const* name; int num_free; unsigned int index; int /*<<< orphan*/  list; struct virtio_device* vdev; } ;
struct vring {int num; TYPE_2__* desc; TYPE_1__* avail; } ;
struct TYPE_6__ {unsigned int avail_flags_shadow; int /*<<< orphan*/  desc_state; struct vring vring; scalar_t__ avail_idx_shadow; scalar_t__ queue_size_in_bytes; scalar_t__ queue_dma_addr; } ;
struct vring_virtqueue {int packed_ring; int we_own_ring; int (* notify ) (struct virtqueue*) ;int weak_barriers; int broken; int in_use; int last_add_time_valid; int indirect; struct virtqueue vq; TYPE_3__ split; scalar_t__ free_head; scalar_t__ event; int /*<<< orphan*/  use_dma_api; scalar_t__ num_added; scalar_t__ last_used_idx; } ;
struct vring_desc_state_split {int dummy; } ;
struct virtio_device {int /*<<< orphan*/  vqs; } ;
struct TYPE_5__ {void* next; } ;
struct TYPE_4__ {void* flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_F_ORDER_PLATFORM ; 
 int /*<<< orphan*/  VIRTIO_F_RING_PACKED ; 
 int /*<<< orphan*/  VIRTIO_RING_F_EVENT_IDX ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 unsigned int VRING_AVAIL_F_NO_INTERRUPT ; 
 void* cpu_to_virtio16 (struct virtio_device*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct vring_virtqueue*) ; 
 struct vring_virtqueue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_use_dma_api (struct virtio_device*) ; 

struct virtqueue *__vring_new_virtqueue(unsigned int index,
					struct vring vring,
					struct virtio_device *vdev,
					bool weak_barriers,
					bool context,
					bool (*notify)(struct virtqueue *),
					void (*callback)(struct virtqueue *),
					const char *name)
{
	unsigned int i;
	struct vring_virtqueue *vq;

	if (virtio_has_feature(vdev, VIRTIO_F_RING_PACKED))
		return NULL;

	vq = kmalloc(sizeof(*vq), GFP_KERNEL);
	if (!vq)
		return NULL;

	vq->packed_ring = false;
	vq->vq.callback = callback;
	vq->vq.vdev = vdev;
	vq->vq.name = name;
	vq->vq.num_free = vring.num;
	vq->vq.index = index;
	vq->we_own_ring = false;
	vq->notify = notify;
	vq->weak_barriers = weak_barriers;
	vq->broken = false;
	vq->last_used_idx = 0;
	vq->num_added = 0;
	vq->use_dma_api = vring_use_dma_api(vdev);
	list_add_tail(&vq->vq.list, &vdev->vqs);
#ifdef DEBUG
	vq->in_use = false;
	vq->last_add_time_valid = false;
#endif

	vq->indirect = virtio_has_feature(vdev, VIRTIO_RING_F_INDIRECT_DESC) &&
		!context;
	vq->event = virtio_has_feature(vdev, VIRTIO_RING_F_EVENT_IDX);

	if (virtio_has_feature(vdev, VIRTIO_F_ORDER_PLATFORM))
		vq->weak_barriers = false;

	vq->split.queue_dma_addr = 0;
	vq->split.queue_size_in_bytes = 0;

	vq->split.vring = vring;
	vq->split.avail_flags_shadow = 0;
	vq->split.avail_idx_shadow = 0;

	/* No callback?  Tell other side not to bother us. */
	if (!callback) {
		vq->split.avail_flags_shadow |= VRING_AVAIL_F_NO_INTERRUPT;
		if (!vq->event)
			vq->split.vring.avail->flags = cpu_to_virtio16(vdev,
					vq->split.avail_flags_shadow);
	}

	vq->split.desc_state = kmalloc_array(vring.num,
			sizeof(struct vring_desc_state_split), GFP_KERNEL);
	if (!vq->split.desc_state) {
		kfree(vq);
		return NULL;
	}

	/* Put everything in free lists. */
	vq->free_head = 0;
	for (i = 0; i < vring.num-1; i++)
		vq->split.vring.desc[i].next = cpu_to_virtio16(vdev, i + 1);
	memset(vq->split.desc_state, 0, vring.num *
			sizeof(struct vring_desc_state_split));

	return &vq->vq;
}