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
struct vb2_queue {int io_modes; int buf_struct_size; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * lock; struct mcam_camera* drv_priv; int /*<<< orphan*/  type; } ;
struct mcam_vb_buffer {int dummy; } ;
struct mcam_camera {int buffer_mode; int /*<<< orphan*/  frame_complete; int /*<<< orphan*/  dma_setup; int /*<<< orphan*/  s_tasklet; int /*<<< orphan*/  buffers; int /*<<< orphan*/  dev; int /*<<< orphan*/  s_mutex; struct vb2_queue vb_queue; } ;

/* Variables and functions */
#define  B_DMA_contig 130 
#define  B_DMA_sg 129 
#define  B_vmalloc 128 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  mcam_ctlr_dma_contig ; 
 int /*<<< orphan*/  mcam_ctlr_dma_sg ; 
 int /*<<< orphan*/  mcam_ctlr_dma_vmalloc ; 
 int /*<<< orphan*/  mcam_dma_contig_done ; 
 int /*<<< orphan*/  mcam_dma_sg_done ; 
 int /*<<< orphan*/  mcam_frame_tasklet ; 
 int /*<<< orphan*/  mcam_vb2_ops ; 
 int /*<<< orphan*/  mcam_vb2_sg_ops ; 
 int /*<<< orphan*/  mcam_vmalloc_done ; 
 int /*<<< orphan*/  memset (struct vb2_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int /*<<< orphan*/  vb2_dma_sg_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 

__attribute__((used)) static int mcam_setup_vb2(struct mcam_camera *cam)
{
	struct vb2_queue *vq = &cam->vb_queue;

	memset(vq, 0, sizeof(*vq));
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->drv_priv = cam;
	vq->lock = &cam->s_mutex;
	vq->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	vq->buf_struct_size = sizeof(struct mcam_vb_buffer);
	vq->dev = cam->dev;
	INIT_LIST_HEAD(&cam->buffers);
	switch (cam->buffer_mode) {
	case B_DMA_contig:
#ifdef MCAM_MODE_DMA_CONTIG
		vq->ops = &mcam_vb2_ops;
		vq->mem_ops = &vb2_dma_contig_memops;
		cam->dma_setup = mcam_ctlr_dma_contig;
		cam->frame_complete = mcam_dma_contig_done;
#endif
		break;
	case B_DMA_sg:
#ifdef MCAM_MODE_DMA_SG
		vq->ops = &mcam_vb2_sg_ops;
		vq->mem_ops = &vb2_dma_sg_memops;
		cam->dma_setup = mcam_ctlr_dma_sg;
		cam->frame_complete = mcam_dma_sg_done;
#endif
		break;
	case B_vmalloc:
#ifdef MCAM_MODE_VMALLOC
		tasklet_init(&cam->s_tasklet, mcam_frame_tasklet,
				(unsigned long) cam);
		vq->ops = &mcam_vb2_ops;
		vq->mem_ops = &vb2_vmalloc_memops;
		cam->dma_setup = mcam_ctlr_dma_vmalloc;
		cam->frame_complete = mcam_vmalloc_done;
#endif
		break;
	}
	return vb2_queue_init(vq);
}