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
struct vb2_queue {int min_buffers_needed; int buf_struct_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct sun4i_csi* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  io_modes; int /*<<< orphan*/  type; } ;
struct sun4i_csi_buffer {int dummy; } ;
struct sun4i_csi {int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** current_buf; int /*<<< orphan*/  buf_list; int /*<<< orphan*/  qlock; struct vb2_queue queue; } ;

/* Variables and functions */
 int CSI_MAX_BUFFER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  VB2_MMAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun4i_csi*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4i_csi_irq ; 
 int /*<<< orphan*/  sun4i_csi_qops ; 
 int v4l2_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_queue_release (struct vb2_queue*) ; 

int sun4i_csi_dma_register(struct sun4i_csi *csi, int irq)
{
	struct vb2_queue *q = &csi->queue;
	int ret;
	int i;

	spin_lock_init(&csi->qlock);
	mutex_init(&csi->lock);

	INIT_LIST_HEAD(&csi->buf_list);
	for (i = 0; i < CSI_MAX_BUFFER; i++)
		csi->current_buf[i] = NULL;

	q->min_buffers_needed = 3;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_MMAP;
	q->lock = &csi->lock;
	q->drv_priv = csi;
	q->buf_struct_size = sizeof(struct sun4i_csi_buffer);
	q->ops = &sun4i_csi_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->dev = csi->dev;

	ret = vb2_queue_init(q);
	if (ret < 0) {
		dev_err(csi->dev, "failed to initialize VB2 queue\n");
		goto err_free_mutex;
	}

	ret = v4l2_device_register(csi->dev, &csi->v4l);
	if (ret) {
		dev_err(csi->dev, "Couldn't register the v4l2 device\n");
		goto err_free_queue;
	}

	ret = devm_request_irq(csi->dev, irq, sun4i_csi_irq, 0,
			       dev_name(csi->dev), csi);
	if (ret) {
		dev_err(csi->dev, "Couldn't register our interrupt\n");
		goto err_unregister_device;
	}

	return 0;

err_unregister_device:
	v4l2_device_unregister(&csi->v4l);

err_free_queue:
	vb2_queue_release(q);

err_free_mutex:
	mutex_destroy(&csi->lock);
	return ret;
}