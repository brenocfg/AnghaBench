#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_rect {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; scalar_t__ member_1; scalar_t__ member_0; } ;
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; } ;
struct vivid_dev {struct v4l2_rect loop_vid_overlay_cap; struct v4l2_rect loop_vid_overlay; struct v4l2_rect loop_fb_copy; TYPE_1__ compose_cap; struct v4l2_rect crop_cap; scalar_t__ overlay_out_top; struct v4l2_rect compose_out; scalar_t__ overlay_out_left; struct v4l2_rect loop_vid_copy; struct v4l2_rect loop_vid_cap; struct v4l2_rect loop_vid_out; TYPE_1__ crop_out; int /*<<< orphan*/  display_height; int /*<<< orphan*/  display_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_rect_intersect (struct v4l2_rect*,struct v4l2_rect*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  v4l2_rect_scale (struct v4l2_rect*,struct v4l2_rect*,TYPE_1__*) ; 

__attribute__((used)) static void vivid_precalc_copy_rects(struct vivid_dev *dev)
{
	/* Framebuffer rectangle */
	struct v4l2_rect r_fb = {
		0, 0, dev->display_width, dev->display_height
	};
	/* Overlay window rectangle in framebuffer coordinates */
	struct v4l2_rect r_overlay = {
		dev->overlay_out_left, dev->overlay_out_top,
		dev->compose_out.width, dev->compose_out.height
	};

	v4l2_rect_intersect(&dev->loop_vid_copy, &dev->crop_cap, &dev->compose_out);

	dev->loop_vid_out = dev->loop_vid_copy;
	v4l2_rect_scale(&dev->loop_vid_out, &dev->compose_out, &dev->crop_out);
	dev->loop_vid_out.left += dev->crop_out.left;
	dev->loop_vid_out.top += dev->crop_out.top;

	dev->loop_vid_cap = dev->loop_vid_copy;
	v4l2_rect_scale(&dev->loop_vid_cap, &dev->crop_cap, &dev->compose_cap);

	dprintk(dev, 1,
		"loop_vid_copy: %dx%d@%dx%d loop_vid_out: %dx%d@%dx%d loop_vid_cap: %dx%d@%dx%d\n",
		dev->loop_vid_copy.width, dev->loop_vid_copy.height,
		dev->loop_vid_copy.left, dev->loop_vid_copy.top,
		dev->loop_vid_out.width, dev->loop_vid_out.height,
		dev->loop_vid_out.left, dev->loop_vid_out.top,
		dev->loop_vid_cap.width, dev->loop_vid_cap.height,
		dev->loop_vid_cap.left, dev->loop_vid_cap.top);

	v4l2_rect_intersect(&r_overlay, &r_fb, &r_overlay);

	/* shift r_overlay to the same origin as compose_out */
	r_overlay.left += dev->compose_out.left - dev->overlay_out_left;
	r_overlay.top += dev->compose_out.top - dev->overlay_out_top;

	v4l2_rect_intersect(&dev->loop_vid_overlay, &r_overlay, &dev->loop_vid_copy);
	dev->loop_fb_copy = dev->loop_vid_overlay;

	/* shift dev->loop_fb_copy back again to the fb origin */
	dev->loop_fb_copy.left -= dev->compose_out.left - dev->overlay_out_left;
	dev->loop_fb_copy.top -= dev->compose_out.top - dev->overlay_out_top;

	dev->loop_vid_overlay_cap = dev->loop_vid_overlay;
	v4l2_rect_scale(&dev->loop_vid_overlay_cap, &dev->crop_cap, &dev->compose_cap);

	dprintk(dev, 1,
		"loop_fb_copy: %dx%d@%dx%d loop_vid_overlay: %dx%d@%dx%d loop_vid_overlay_cap: %dx%d@%dx%d\n",
		dev->loop_fb_copy.width, dev->loop_fb_copy.height,
		dev->loop_fb_copy.left, dev->loop_fb_copy.top,
		dev->loop_vid_overlay.width, dev->loop_vid_overlay.height,
		dev->loop_vid_overlay.left, dev->loop_vid_overlay.top,
		dev->loop_vid_overlay_cap.width, dev->loop_vid_overlay_cap.height,
		dev->loop_vid_overlay_cap.left, dev->loop_vid_overlay_cap.top);
}