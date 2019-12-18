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
struct video_device {scalar_t__ vfl_type; } ;
struct file {struct bttv_fh* private_data; } ;
struct TYPE_4__ {scalar_t__ setup_ok; } ;
struct bttv_fh {int type; int do_crop; int /*<<< orphan*/  fh; int /*<<< orphan*/  vbi_fmt; int /*<<< orphan*/  vbi; int /*<<< orphan*/  cap; TYPE_1__ ov; } ;
struct bttv_buffer {int dummy; } ;
struct TYPE_6__ {TYPE_2__* pci; int /*<<< orphan*/  nr; } ;
struct bttv {int /*<<< orphan*/  tvnorm; int /*<<< orphan*/  mute; int /*<<< orphan*/  input; int /*<<< orphan*/  lock; int /*<<< orphan*/  s_lock; TYPE_3__ c; struct bttv_fh init; int /*<<< orphan*/  users; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 scalar_t__ VFL_TYPE_VBI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  audio_mute (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_field_count (struct bttv*) ; 
 int /*<<< orphan*/  bttv_vbi_fmt_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_vbi_qops ; 
 int /*<<< orphan*/  bttv_video_qops ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,...) ; 
 struct bttv_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_crop ; 
 int /*<<< orphan*/  set_input (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tvnorm (struct bttv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 int /*<<< orphan*/ * v4l2_type_names ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct bttv* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_queue_sg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,struct bttv_fh*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bttv_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct bttv *btv = video_drvdata(file);
	struct bttv_fh *fh;
	enum v4l2_buf_type type = 0;

	dprintk("open dev=%s\n", video_device_node_name(vdev));

	if (vdev->vfl_type == VFL_TYPE_GRABBER) {
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	} else if (vdev->vfl_type == VFL_TYPE_VBI) {
		type = V4L2_BUF_TYPE_VBI_CAPTURE;
	} else {
		WARN_ON(1);
		return -ENODEV;
	}

	dprintk("%d: open called (type=%s)\n",
		btv->c.nr, v4l2_type_names[type]);

	/* allocate per filehandle data */
	fh = kmalloc(sizeof(*fh), GFP_KERNEL);
	if (unlikely(!fh))
		return -ENOMEM;
	btv->users++;
	file->private_data = fh;

	*fh = btv->init;
	v4l2_fh_init(&fh->fh, vdev);

	fh->type = type;
	fh->ov.setup_ok = 0;

	videobuf_queue_sg_init(&fh->cap, &bttv_video_qops,
			    &btv->c.pci->dev, &btv->s_lock,
			    V4L2_BUF_TYPE_VIDEO_CAPTURE,
			    V4L2_FIELD_INTERLACED,
			    sizeof(struct bttv_buffer),
			    fh, &btv->lock);
	videobuf_queue_sg_init(&fh->vbi, &bttv_vbi_qops,
			    &btv->c.pci->dev, &btv->s_lock,
			    V4L2_BUF_TYPE_VBI_CAPTURE,
			    V4L2_FIELD_SEQ_TB,
			    sizeof(struct bttv_buffer),
			    fh, &btv->lock);
	set_tvnorm(btv,btv->tvnorm);
	set_input(btv, btv->input, btv->tvnorm);
	audio_mute(btv, btv->mute);

	/* The V4L2 spec requires one global set of cropping parameters
	   which only change on request. These are stored in btv->crop[1].
	   However for compatibility with V4L apps and cropping unaware
	   V4L2 apps we now reset the cropping parameters as seen through
	   this fh, which is to say VIDIOC_G_SELECTION and scaling limit checks
	   will use btv->crop[0], the default cropping parameters for the
	   current video standard, and VIDIOC_S_FMT will not implicitly
	   change the cropping parameters until VIDIOC_S_SELECTION has been
	   called. */
	fh->do_crop = !reset_crop; /* module parameter */

	/* Likewise there should be one global set of VBI capture
	   parameters, but for compatibility with V4L apps and earlier
	   driver versions each fh has its own parameters. */
	bttv_vbi_fmt_reset(&fh->vbi_fmt, btv->tvnorm);

	bttv_field_count(btv);
	v4l2_fh_add(&fh->fh);
	return 0;
}