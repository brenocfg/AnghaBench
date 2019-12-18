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
struct vb2_queue {scalar_t__ type; } ;
struct au0828_dev {scalar_t__ streaming_users; int vid_timeout_running; int vbi_timeout_running; int /*<<< orphan*/  vbi_timeout; int /*<<< orphan*/  vid_timeout; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  max_pkt_size; scalar_t__ vbi_frame_count; scalar_t__ frame_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU0828_ISO_PACKETS_PER_URB ; 
 int /*<<< orphan*/  AU0828_MAX_ISO_BUFS ; 
 int HZ ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  au0828_i2s_init (struct au0828_dev*) ; 
 int au0828_init_isoc (struct au0828_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au0828_isoc_copy ; 
 int /*<<< orphan*/  dprintk (int,char*,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct au0828_dev* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 

int au0828_start_analog_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct au0828_dev *dev = vb2_get_drv_priv(vq);
	int rc = 0;

	dprintk(1, "au0828_start_analog_streaming called %d\n",
		dev->streaming_users);

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		dev->frame_count = 0;
	else
		dev->vbi_frame_count = 0;

	if (dev->streaming_users == 0) {
		/* If we were doing ac97 instead of i2s, it would go here...*/
		au0828_i2s_init(dev);
		rc = au0828_init_isoc(dev, AU0828_ISO_PACKETS_PER_URB,
				   AU0828_MAX_ISO_BUFS, dev->max_pkt_size,
				   au0828_isoc_copy);
		if (rc < 0) {
			pr_info("au0828_init_isoc failed\n");
			return rc;
		}

		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 1);

		if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
			dev->vid_timeout_running = 1;
			mod_timer(&dev->vid_timeout, jiffies + (HZ / 10));
		} else if (vq->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
			dev->vbi_timeout_running = 1;
			mod_timer(&dev->vbi_timeout, jiffies + (HZ / 10));
		}
	}
	dev->streaming_users++;
	return rc;
}