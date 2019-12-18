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
struct vb2_buffer {size_t index; TYPE_1__* vb2_queue; } ;
struct sg_dma_desc_info {int dummy; } ;
struct cobalt_stream {struct sg_dma_desc_info* dma_desc_info; } ;
struct TYPE_2__ {struct cobalt_stream* drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  descriptor_list_free (struct sg_dma_desc_info*) ; 

__attribute__((used)) static void cobalt_buf_cleanup(struct vb2_buffer *vb)
{
	struct cobalt_stream *s = vb->vb2_queue->drv_priv;
	struct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];

	descriptor_list_free(desc);
}