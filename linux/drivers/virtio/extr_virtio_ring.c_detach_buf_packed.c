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
typedef  int u32 ;
struct TYPE_5__ {TYPE_3__* desc_extra; struct vring_desc_state_packed* desc_state; } ;
struct TYPE_4__ {unsigned int num_free; } ;
struct vring_virtqueue {unsigned int free_head; TYPE_2__ packed; scalar_t__ use_dma_api; scalar_t__ indirect; TYPE_1__ vq; } ;
struct vring_packed_desc {int dummy; } ;
struct vring_desc_state_packed {size_t last; unsigned int next; unsigned int num; struct vring_packed_desc* indir_desc; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vring_packed_desc*) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  vring_unmap_desc_packed (struct vring_virtqueue*,struct vring_packed_desc*) ; 
 int /*<<< orphan*/  vring_unmap_state_packed (struct vring_virtqueue*,TYPE_3__*) ; 

__attribute__((used)) static void detach_buf_packed(struct vring_virtqueue *vq,
			      unsigned int id, void **ctx)
{
	struct vring_desc_state_packed *state = NULL;
	struct vring_packed_desc *desc;
	unsigned int i, curr;

	state = &vq->packed.desc_state[id];

	/* Clear data ptr. */
	state->data = NULL;

	vq->packed.desc_state[state->last].next = vq->free_head;
	vq->free_head = id;
	vq->vq.num_free += state->num;

	if (unlikely(vq->use_dma_api)) {
		curr = id;
		for (i = 0; i < state->num; i++) {
			vring_unmap_state_packed(vq,
				&vq->packed.desc_extra[curr]);
			curr = vq->packed.desc_state[curr].next;
		}
	}

	if (vq->indirect) {
		u32 len;

		/* Free the indirect table, if any, now that it's unmapped. */
		desc = state->indir_desc;
		if (!desc)
			return;

		if (vq->use_dma_api) {
			len = vq->packed.desc_extra[id].len;
			for (i = 0; i < len / sizeof(struct vring_packed_desc);
					i++)
				vring_unmap_desc_packed(vq, &desc[i]);
		}
		kfree(desc);
		state->indir_desc = NULL;
	} else if (ctx) {
		*ctx = state->indir_desc;
	}
}