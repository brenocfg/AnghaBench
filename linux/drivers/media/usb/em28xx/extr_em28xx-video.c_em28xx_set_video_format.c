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
struct em28xx_v4l2 {unsigned int width; unsigned int height; int /*<<< orphan*/  vscale; int /*<<< orphan*/  hscale; struct em28xx_fmt* format; } ;
struct em28xx_fmt {int dummy; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  em28xx_resolution_set (struct em28xx*) ; 
 struct em28xx_fmt* format_by_fourcc (unsigned int) ; 
 int /*<<< orphan*/  size_to_scale (struct em28xx*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_set_video_format(struct em28xx *dev, unsigned int fourcc,
				   unsigned int width, unsigned int height)
{
	struct em28xx_fmt     *fmt;
	struct em28xx_v4l2    *v4l2 = dev->v4l2;

	fmt = format_by_fourcc(fourcc);
	if (!fmt)
		return -EINVAL;

	v4l2->format = fmt;
	v4l2->width  = width;
	v4l2->height = height;

	/* set new image size */
	size_to_scale(dev, v4l2->width, v4l2->height,
		      &v4l2->hscale, &v4l2->vscale);

	em28xx_resolution_set(dev);

	return 0;
}