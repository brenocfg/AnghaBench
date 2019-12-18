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
struct vb2_buffer {size_t index; TYPE_1__* vb2_queue; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct sg_dma_desc_info {int /*<<< orphan*/ * virt; int /*<<< orphan*/ * dev; } ;
struct cobalt_stream {unsigned int stride; unsigned int height; int width; int bpp; int /*<<< orphan*/  is_output; scalar_t__ is_audio; struct sg_dma_desc_info* dma_desc_info; struct cobalt* cobalt; } ;
struct cobalt {TYPE_2__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct cobalt_stream* drv_priv; } ;

/* Variables and functions */
 int COBALT_MAX_BPP ; 
 size_t const COBALT_MAX_HEIGHT ; 
 int COBALT_MAX_WIDTH ; 
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  cobalt_info (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  descriptor_list_allocate (struct sg_dma_desc_info*,size_t const) ; 
 int descriptor_list_create (struct cobalt*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int,unsigned int,struct sg_dma_desc_info*) ; 
 int /*<<< orphan*/  descriptor_list_free (struct sg_dma_desc_info*) ; 
 struct sg_table* vb2_dma_sg_plane_desc (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 unsigned int vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cobalt_buf_init(struct vb2_buffer *vb)
{
	struct cobalt_stream *s = vb->vb2_queue->drv_priv;
	struct cobalt *cobalt = s->cobalt;
	const size_t max_pages_per_line =
		(COBALT_MAX_WIDTH * COBALT_MAX_BPP) / PAGE_SIZE + 2;
	const size_t bytes =
		COBALT_MAX_HEIGHT * max_pages_per_line * 0x20;
	const size_t audio_bytes = ((1920 * 4) / PAGE_SIZE + 1) * 0x20;
	struct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	struct sg_table *sg_desc = vb2_dma_sg_plane_desc(vb, 0);
	unsigned size;
	int ret;

	size = s->stride * s->height;
	if (vb2_plane_size(vb, 0) < size) {
		cobalt_info("data will not fit into plane (%lu < %u)\n",
					vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	if (desc->virt == NULL) {
		desc->dev = &cobalt->pci_dev->dev;
		descriptor_list_allocate(desc,
			s->is_audio ? audio_bytes : bytes);
		if (desc->virt == NULL)
			return -ENOMEM;
	}
	ret = descriptor_list_create(cobalt, sg_desc->sgl,
			!s->is_output, sg_desc->nents, size,
			s->width * s->bpp, s->stride, desc);
	if (ret)
		descriptor_list_free(desc);
	return ret;
}