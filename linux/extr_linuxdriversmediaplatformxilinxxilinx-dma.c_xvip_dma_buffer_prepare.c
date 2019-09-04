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
struct xvip_dma_buffer {struct xvip_dma* dma; } ;
struct xvip_dma {int dummy; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct xvip_dma_buffer* to_xvip_dma_buffer (struct vb2_v4l2_buffer*) ; 
 struct xvip_dma* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xvip_dma_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct xvip_dma *dma = vb2_get_drv_priv(vb->vb2_queue);
	struct xvip_dma_buffer *buf = to_xvip_dma_buffer(vbuf);

	buf->dma = dma;

	return 0;
}