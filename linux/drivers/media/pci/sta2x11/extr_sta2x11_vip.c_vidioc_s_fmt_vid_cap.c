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
struct TYPE_4__ {int field; int height; int width; } ;
struct TYPE_3__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct sta2x11_vip {int /*<<< orphan*/  slock; int /*<<< orphan*/  v4l2_dev; TYPE_2__ format; int /*<<< orphan*/  vb_vidq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVP_BFO ; 
 int /*<<< orphan*/  DVP_BFS ; 
 int /*<<< orphan*/  DVP_TFO ; 
 int /*<<< orphan*/  DVP_TFS ; 
 int /*<<< orphan*/  DVP_VMP ; 
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_FIELD_BOTTOM 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  reg_write (struct sta2x11_vip*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct sta2x11_vip* video_drvdata (struct file*) ; 
 int vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct sta2x11_vip *vip = video_drvdata(file);
	unsigned int t_stop, b_stop, pitch;
	int ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	if (ret)
		return ret;

	if (vb2_is_busy(&vip->vb_vidq)) {
		/* Can't change format during acquisition */
		v4l2_err(&vip->v4l2_dev, "device busy\n");
		return -EBUSY;
	}
	vip->format = f->fmt.pix;
	switch (vip->format.field) {
	case V4L2_FIELD_INTERLACED:
		t_stop = ((vip->format.height / 2 - 1) << 16) |
			 (2 * vip->format.width - 1);
		b_stop = t_stop;
		pitch = 4 * vip->format.width;
		break;
	case V4L2_FIELD_TOP:
		t_stop = ((vip->format.height - 1) << 16) |
			 (2 * vip->format.width - 1);
		b_stop = (0 << 16) | (2 * vip->format.width - 1);
		pitch = 2 * vip->format.width;
		break;
	case V4L2_FIELD_BOTTOM:
		t_stop = (0 << 16) | (2 * vip->format.width - 1);
		b_stop = (vip->format.height << 16) |
			 (2 * vip->format.width - 1);
		pitch = 2 * vip->format.width;
		break;
	default:
		v4l2_err(&vip->v4l2_dev, "unknown field format\n");
		return -EINVAL;
	}

	spin_lock_irq(&vip->slock);
	/* Y-X Top Field Offset */
	reg_write(vip, DVP_TFO, 0);
	/* Y-X Bottom Field Offset */
	reg_write(vip, DVP_BFO, 0);
	/* Y-X Top Field Stop*/
	reg_write(vip, DVP_TFS, t_stop);
	/* Y-X Bottom Field Stop */
	reg_write(vip, DVP_BFS, b_stop);
	/* Video Memory Pitch */
	reg_write(vip, DVP_VMP, pitch);
	spin_unlock_irq(&vip->slock);

	return 0;
}