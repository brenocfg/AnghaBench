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
struct video_device {int vfl_type; } ;
struct tm6000_fh {int radio; int type; int /*<<< orphan*/  fh; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; struct tm6000_core* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  active; int /*<<< orphan*/  queued; } ;
struct tm6000_core {int radio; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  mode; TYPE_1__ vidq; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  users; } ;
struct tm6000_buffer {int dummy; } ;
struct file {struct tm6000_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TM6000_MODE_ANALOG ; 
 int V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_DEBUG_OPEN ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
#define  VFL_TYPE_GRABBER 130 
#define  VFL_TYPE_RADIO 129 
#define  VFL_TYPE_VBI 128 
 int /*<<< orphan*/  dprintk (struct tm6000_core*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* format ; 
 int /*<<< orphan*/  format_by_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tm6000_fh*) ; 
 struct tm6000_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  tm6000_get_std_res (struct tm6000_core*) ; 
 int tm6000_init_analog_mode (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_prepare_isoc (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_set_audio_rinput (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_start_thread (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_video_qops ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 int /*<<< orphan*/ * v4l2_type_names ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct tm6000_core* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_queue_vmalloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,struct tm6000_fh*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __tm6000_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct tm6000_core *dev = video_drvdata(file);
	struct tm6000_fh *fh;
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	int rc;
	int radio = 0;

	dprintk(dev, V4L2_DEBUG_OPEN, "tm6000: open called (dev=%s)\n",
		video_device_node_name(vdev));

	switch (vdev->vfl_type) {
	case VFL_TYPE_GRABBER:
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		break;
	case VFL_TYPE_VBI:
		type = V4L2_BUF_TYPE_VBI_CAPTURE;
		break;
	case VFL_TYPE_RADIO:
		radio = 1;
		break;
	default:
		return -EINVAL;
	}

	/* If more than one user, mutex should be added */
	dev->users++;

	dprintk(dev, V4L2_DEBUG_OPEN, "open dev=%s type=%s users=%d\n",
		video_device_node_name(vdev), v4l2_type_names[type],
		dev->users);

	/* allocate + initialize per filehandle data */
	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (NULL == fh) {
		dev->users--;
		return -ENOMEM;
	}

	v4l2_fh_init(&fh->fh, vdev);
	file->private_data = fh;
	fh->dev      = dev;
	fh->radio    = radio;
	dev->radio   = radio;
	fh->type     = type;
	dev->fourcc  = format[0].fourcc;

	fh->fmt      = format_by_fourcc(dev->fourcc);

	tm6000_get_std_res(dev);

	fh->width = dev->width;
	fh->height = dev->height;

	dprintk(dev, V4L2_DEBUG_OPEN, "Open: fh=%p, dev=%p, dev->vidq=%p\n",
		fh, dev, &dev->vidq);
	dprintk(dev, V4L2_DEBUG_OPEN, "Open: list_empty queued=%d\n",
		list_empty(&dev->vidq.queued));
	dprintk(dev, V4L2_DEBUG_OPEN, "Open: list_empty active=%d\n",
		list_empty(&dev->vidq.active));

	/* initialize hardware on analog mode */
	rc = tm6000_init_analog_mode(dev);
	if (rc < 0) {
		v4l2_fh_exit(&fh->fh);
		kfree(fh);
		return rc;
	}

	dev->mode = TM6000_MODE_ANALOG;

	if (!fh->radio) {
		videobuf_queue_vmalloc_init(&fh->vb_vidq, &tm6000_video_qops,
				NULL, &dev->slock,
				fh->type,
				V4L2_FIELD_INTERLACED,
				sizeof(struct tm6000_buffer), fh, &dev->lock);
	} else {
		dprintk(dev, V4L2_DEBUG_OPEN, "video_open: setting radio device\n");
		tm6000_set_audio_rinput(dev);
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_radio);
		tm6000_prepare_isoc(dev);
		tm6000_start_thread(dev);
	}
	v4l2_fh_add(&fh->fh);

	return 0;
}