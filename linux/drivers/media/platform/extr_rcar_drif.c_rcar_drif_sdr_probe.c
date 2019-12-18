#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int io_modes; int buf_struct_size; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct rcar_drif_sdr* drv_priv; int /*<<< orphan*/  type; } ;
struct rcar_drif_sdr {int /*<<< orphan*/  v4l2_dev; TYPE_2__ notifier; int /*<<< orphan*/  dev; TYPE_1__ vb_queue; int /*<<< orphan*/  queued_bufs; int /*<<< orphan*/  dma_lock; int /*<<< orphan*/  queued_bufs_lock; int /*<<< orphan*/  vb_queue_mutex; int /*<<< orphan*/  v4l2_mutex; int /*<<< orphan*/  hwbuf_size; } ;
struct rcar_drif_frame_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCAR_DRIF_DEFAULT_HWBUF_SIZE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_SDR_CAPTURE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_drif_notify_ops ; 
 int rcar_drif_parse_subdevs (struct rcar_drif_sdr*) ; 
 int rcar_drif_set_default_format (struct rcar_drif_sdr*) ; 
 int /*<<< orphan*/  rcar_drif_vb2_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_2__*) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int v4l2_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int vb2_queue_init (TYPE_1__*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 

__attribute__((used)) static int rcar_drif_sdr_probe(struct rcar_drif_sdr *sdr)
{
	int ret;

	/* Validate any supported format for enabled channels */
	ret = rcar_drif_set_default_format(sdr);
	if (ret) {
		dev_err(sdr->dev, "failed to set default format\n");
		return ret;
	}

	/* Set defaults */
	sdr->hwbuf_size = RCAR_DRIF_DEFAULT_HWBUF_SIZE;

	mutex_init(&sdr->v4l2_mutex);
	mutex_init(&sdr->vb_queue_mutex);
	spin_lock_init(&sdr->queued_bufs_lock);
	spin_lock_init(&sdr->dma_lock);
	INIT_LIST_HEAD(&sdr->queued_bufs);

	/* Init videobuf2 queue structure */
	sdr->vb_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	sdr->vb_queue.io_modes = VB2_READ | VB2_MMAP | VB2_DMABUF;
	sdr->vb_queue.drv_priv = sdr;
	sdr->vb_queue.buf_struct_size = sizeof(struct rcar_drif_frame_buf);
	sdr->vb_queue.ops = &rcar_drif_vb2_ops;
	sdr->vb_queue.mem_ops = &vb2_vmalloc_memops;
	sdr->vb_queue.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	/* Init videobuf2 queue */
	ret = vb2_queue_init(&sdr->vb_queue);
	if (ret) {
		dev_err(sdr->dev, "failed: vb2_queue_init ret %d\n", ret);
		return ret;
	}

	/* Register the v4l2_device */
	ret = v4l2_device_register(sdr->dev, &sdr->v4l2_dev);
	if (ret) {
		dev_err(sdr->dev, "failed: v4l2_device_register ret %d\n", ret);
		return ret;
	}

	/*
	 * Parse subdevs after v4l2_device_register because if the subdev
	 * is already probed, bound and complete will be called immediately
	 */
	ret = rcar_drif_parse_subdevs(sdr);
	if (ret)
		goto error;

	sdr->notifier.ops = &rcar_drif_notify_ops;

	/* Register notifier */
	ret = v4l2_async_notifier_register(&sdr->v4l2_dev, &sdr->notifier);
	if (ret < 0) {
		dev_err(sdr->dev, "failed: notifier register ret %d\n", ret);
		goto cleanup;
	}

	return ret;

cleanup:
	v4l2_async_notifier_cleanup(&sdr->notifier);
error:
	v4l2_device_unregister(&sdr->v4l2_dev);

	return ret;
}