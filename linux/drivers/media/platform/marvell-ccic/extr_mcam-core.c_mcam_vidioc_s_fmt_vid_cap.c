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
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct mcam_format_struct {int /*<<< orphan*/  mbus_code; } ;
struct mcam_camera {scalar_t__ state; scalar_t__ buffer_mode; int /*<<< orphan*/  mbus_code; TYPE_1__ pix_format; int /*<<< orphan*/  vb_queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ B_vmalloc ; 
 int EBUSY ; 
 scalar_t__ S_IDLE ; 
 int mcam_check_dma_buffers (struct mcam_camera*) ; 
 struct mcam_format_struct* mcam_find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_set_config_needed (struct mcam_camera*,int) ; 
 int mcam_vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct mcam_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int mcam_vidioc_s_fmt_vid_cap(struct file *filp, void *priv,
		struct v4l2_format *fmt)
{
	struct mcam_camera *cam = video_drvdata(filp);
	struct mcam_format_struct *f;
	int ret;

	/*
	 * Can't do anything if the device is not idle
	 * Also can't if there are streaming buffers in place.
	 */
	if (cam->state != S_IDLE || vb2_is_busy(&cam->vb_queue))
		return -EBUSY;

	f = mcam_find_format(fmt->fmt.pix.pixelformat);

	/*
	 * See if the formatting works in principle.
	 */
	ret = mcam_vidioc_try_fmt_vid_cap(filp, priv, fmt);
	if (ret)
		return ret;
	/*
	 * Now we start to change things for real, so let's do it
	 * under lock.
	 */
	cam->pix_format = fmt->fmt.pix;
	cam->mbus_code = f->mbus_code;

	/*
	 * Make sure we have appropriate DMA buffers.
	 */
	if (cam->buffer_mode == B_vmalloc) {
		ret = mcam_check_dma_buffers(cam);
		if (ret)
			goto out;
	}
	mcam_set_config_needed(cam, 1);
out:
	return ret;
}