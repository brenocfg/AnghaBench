#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_10__ {size_t num; TYPE_2__* desc; } ;
struct TYPE_12__ {size_t next_avail_idx; size_t avail_used_flags; int avail_wrap_counter; TYPE_5__* desc_state; TYPE_4__ vring; TYPE_1__* desc_extra; } ;
struct TYPE_9__ {int num_free; } ;
struct vring_virtqueue {size_t free_head; int num_added; TYPE_6__ packed; TYPE_3__ vq; int /*<<< orphan*/  weak_barriers; scalar_t__ use_dma_api; } ;
struct vring_packed_desc {void* len; void* addr; void* flags; } ;
struct scatterlist {unsigned int length; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_11__ {size_t next; int num; size_t last; struct vring_packed_desc* indir_desc; void* data; } ;
struct TYPE_8__ {void* flags; void* id; void* len; void* addr; } ;
struct TYPE_7__ {unsigned int len; size_t flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int ENOSPC ; 
 size_t VRING_DESC_F_INDIRECT ; 
 size_t VRING_DESC_F_WRITE ; 
 int VRING_PACKED_DESC_F_AVAIL ; 
 int VRING_PACKED_DESC_F_USED ; 
 struct vring_packed_desc* alloc_indirect_packed (unsigned int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le32 (unsigned int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vring_packed_desc*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtio_wmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_map_one_sg (struct vring_virtqueue*,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_map_single (struct vring_virtqueue*,struct vring_packed_desc*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ vring_mapping_error (struct vring_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_unmap_desc_packed (struct vring_virtqueue*,struct vring_packed_desc*) ; 

__attribute__((used)) static int virtqueue_add_indirect_packed(struct vring_virtqueue *vq,
				       struct scatterlist *sgs[],
				       unsigned int total_sg,
				       unsigned int out_sgs,
				       unsigned int in_sgs,
				       void *data,
				       gfp_t gfp)
{
	struct vring_packed_desc *desc;
	struct scatterlist *sg;
	unsigned int i, n, err_idx;
	u16 head, id;
	dma_addr_t addr;

	head = vq->packed.next_avail_idx;
	desc = alloc_indirect_packed(total_sg, gfp);

	if (unlikely(vq->vq.num_free < 1)) {
		pr_debug("Can't add buf len 1 - avail = 0\n");
		kfree(desc);
		END_USE(vq);
		return -ENOSPC;
	}

	i = 0;
	id = vq->free_head;
	BUG_ON(id == vq->packed.vring.num);

	for (n = 0; n < out_sgs + in_sgs; n++) {
		for (sg = sgs[n]; sg; sg = sg_next(sg)) {
			addr = vring_map_one_sg(vq, sg, n < out_sgs ?
					DMA_TO_DEVICE : DMA_FROM_DEVICE);
			if (vring_mapping_error(vq, addr))
				goto unmap_release;

			desc[i].flags = cpu_to_le16(n < out_sgs ?
						0 : VRING_DESC_F_WRITE);
			desc[i].addr = cpu_to_le64(addr);
			desc[i].len = cpu_to_le32(sg->length);
			i++;
		}
	}

	/* Now that the indirect table is filled in, map it. */
	addr = vring_map_single(vq, desc,
			total_sg * sizeof(struct vring_packed_desc),
			DMA_TO_DEVICE);
	if (vring_mapping_error(vq, addr))
		goto unmap_release;

	vq->packed.vring.desc[head].addr = cpu_to_le64(addr);
	vq->packed.vring.desc[head].len = cpu_to_le32(total_sg *
				sizeof(struct vring_packed_desc));
	vq->packed.vring.desc[head].id = cpu_to_le16(id);

	if (vq->use_dma_api) {
		vq->packed.desc_extra[id].addr = addr;
		vq->packed.desc_extra[id].len = total_sg *
				sizeof(struct vring_packed_desc);
		vq->packed.desc_extra[id].flags = VRING_DESC_F_INDIRECT |
						  vq->packed.avail_used_flags;
	}

	/*
	 * A driver MUST NOT make the first descriptor in the list
	 * available before all subsequent descriptors comprising
	 * the list are made available.
	 */
	virtio_wmb(vq->weak_barriers);
	vq->packed.vring.desc[head].flags = cpu_to_le16(VRING_DESC_F_INDIRECT |
						vq->packed.avail_used_flags);

	/* We're using some buffers from the free list. */
	vq->vq.num_free -= 1;

	/* Update free pointer */
	n = head + 1;
	if (n >= vq->packed.vring.num) {
		n = 0;
		vq->packed.avail_wrap_counter ^= 1;
		vq->packed.avail_used_flags ^=
				1 << VRING_PACKED_DESC_F_AVAIL |
				1 << VRING_PACKED_DESC_F_USED;
	}
	vq->packed.next_avail_idx = n;
	vq->free_head = vq->packed.desc_state[id].next;

	/* Store token and indirect buffer state. */
	vq->packed.desc_state[id].num = 1;
	vq->packed.desc_state[id].data = data;
	vq->packed.desc_state[id].indir_desc = desc;
	vq->packed.desc_state[id].last = id;

	vq->num_added += 1;

	pr_debug("Added buffer head %i to %p\n", head, vq);
	END_USE(vq);

	return 0;

unmap_release:
	err_idx = i;

	for (i = 0; i < err_idx; i++)
		vring_unmap_desc_packed(vq, &desc[i]);

	kfree(desc);

	END_USE(vq);
	return -EIO;
}