#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vpif_disp_buffer {int dummy; } ;
struct video_device {int device_caps; int /*<<< orphan*/ * lock; struct vb2_queue* queue; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  release; int /*<<< orphan*/  name; } ;
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct channel_obj* drv_priv; void* type; } ;
struct TYPE_8__ {void* type; } ;
struct common_obj {int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_queue; struct vb2_queue buffer_queue; TYPE_4__ fmt; int /*<<< orphan*/ * next_frm; int /*<<< orphan*/ * cur_frm; scalar_t__ cbtm_off; scalar_t__ ctop_off; scalar_t__ ybtm_off; scalar_t__ ytop_off; int /*<<< orphan*/ * set_addr; int /*<<< orphan*/  irqlock; } ;
struct TYPE_5__ {TYPE_4__ dv_timings; int /*<<< orphan*/  stdid; } ;
struct channel_obj {int channel_id; struct video_device video_dev; struct common_obj* common; TYPE_1__ video; TYPE_4__ vpifparams; int /*<<< orphan*/  sd; scalar_t__ initialized; } ;
struct TYPE_7__ {struct channel_obj** dev; int /*<<< orphan*/  v4l2_dev; TYPE_2__* config; int /*<<< orphan*/ * sd; } ;
struct TYPE_6__ {scalar_t__ subdev_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 void* V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int VPIF_DISPLAY_MAX_DEVICES ; 
 int /*<<< orphan*/  VPIF_DRIVER_NAME ; 
 int VPIF_NUMOBJECTS ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int /*<<< orphan*/  video_qops ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct channel_obj*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*,struct channel_obj*,struct video_device*) ; 
 int /*<<< orphan*/  vpif_dev ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 int /*<<< orphan*/  vpif_fops ; 
 int /*<<< orphan*/  vpif_ioctl_ops ; 
 TYPE_3__ vpif_obj ; 
 int vpif_set_output (TYPE_2__*,struct channel_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_update_resolution (struct channel_obj*) ; 

__attribute__((used)) static int vpif_probe_complete(void)
{
	struct common_obj *common;
	struct video_device *vdev;
	struct channel_obj *ch;
	struct vb2_queue *q;
	int j, err, k;

	for (j = 0; j < VPIF_DISPLAY_MAX_DEVICES; j++) {
		ch = vpif_obj.dev[j];
		/* Initialize field of the channel objects */
		for (k = 0; k < VPIF_NUMOBJECTS; k++) {
			common = &ch->common[k];
			spin_lock_init(&common->irqlock);
			mutex_init(&common->lock);
			common->set_addr = NULL;
			common->ytop_off = 0;
			common->ybtm_off = 0;
			common->ctop_off = 0;
			common->cbtm_off = 0;
			common->cur_frm = NULL;
			common->next_frm = NULL;
			memset(&common->fmt, 0, sizeof(common->fmt));
		}
		ch->initialized = 0;
		if (vpif_obj.config->subdev_count)
			ch->sd = vpif_obj.sd[0];
		ch->channel_id = j;

		memset(&ch->vpifparams, 0, sizeof(ch->vpifparams));

		ch->common[VPIF_VIDEO_INDEX].fmt.type =
						V4L2_BUF_TYPE_VIDEO_OUTPUT;

		/* select output 0 */
		err = vpif_set_output(vpif_obj.config, ch, 0);
		if (err)
			goto probe_out;

		/* set initial format */
		ch->video.stdid = V4L2_STD_525_60;
		memset(&ch->video.dv_timings, 0, sizeof(ch->video.dv_timings));
		vpif_update_resolution(ch);

		/* Initialize vb2 queue */
		q = &common->buffer_queue;
		q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
		q->drv_priv = ch;
		q->ops = &video_qops;
		q->mem_ops = &vb2_dma_contig_memops;
		q->buf_struct_size = sizeof(struct vpif_disp_buffer);
		q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->min_buffers_needed = 1;
		q->lock = &common->lock;
		q->dev = vpif_dev;
		err = vb2_queue_init(q);
		if (err) {
			vpif_err("vpif_display: vb2_queue_init() failed\n");
			goto probe_out;
		}

		INIT_LIST_HEAD(&common->dma_queue);

		/* register video device */
		vpif_dbg(1, debug, "channel=%p,channel->video_dev=%p\n",
			 ch, &ch->video_dev);

		/* Initialize the video_device structure */
		vdev = &ch->video_dev;
		strscpy(vdev->name, VPIF_DRIVER_NAME, sizeof(vdev->name));
		vdev->release = video_device_release_empty;
		vdev->fops = &vpif_fops;
		vdev->ioctl_ops = &vpif_ioctl_ops;
		vdev->v4l2_dev = &vpif_obj.v4l2_dev;
		vdev->vfl_dir = VFL_DIR_TX;
		vdev->queue = q;
		vdev->lock = &common->lock;
		vdev->device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
		video_set_drvdata(&ch->video_dev, ch);
		err = video_register_device(vdev, VFL_TYPE_GRABBER,
					    (j ? 3 : 2));
		if (err < 0)
			goto probe_out;
	}

	return 0;

probe_out:
	for (k = 0; k < j; k++) {
		ch = vpif_obj.dev[k];
		common = &ch->common[k];
		video_unregister_device(&ch->video_dev);
	}
	return err;
}