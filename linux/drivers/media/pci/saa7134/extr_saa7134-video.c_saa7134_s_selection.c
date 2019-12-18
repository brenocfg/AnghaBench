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
struct v4l2_rect {scalar_t__ top; scalar_t__ height; scalar_t__ left; scalar_t__ width; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; struct v4l2_rect r; } ;
struct saa7134_dev {int /*<<< orphan*/  video_vbq; scalar_t__ overlay_owner; struct v4l2_rect crop_current; struct v4l2_rect crop_bounds; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_s_selection(struct file *file, void *f, struct v4l2_selection *sel)
{
	struct saa7134_dev *dev = video_drvdata(file);
	struct v4l2_rect *b = &dev->crop_bounds;
	struct v4l2_rect *c = &dev->crop_current;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	if (dev->overlay_owner)
		return -EBUSY;
	if (vb2_is_streaming(&dev->video_vbq))
		return -EBUSY;

	*c = sel->r;
	if (c->top < b->top)
		c->top = b->top;
	if (c->top > b->top + b->height)
		c->top = b->top + b->height;
	if (c->height > b->top - c->top + b->height)
		c->height = b->top - c->top + b->height;

	if (c->left < b->left)
		c->left = b->left;
	if (c->left > b->left + b->width)
		c->left = b->left + b->width;
	if (c->width > b->left - c->left + b->width)
		c->width = b->left - c->left + b->width;
	sel->r = *c;
	return 0;
}