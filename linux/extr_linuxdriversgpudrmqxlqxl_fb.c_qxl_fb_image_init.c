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
struct qxl_fb_image {scalar_t__ visual; int /*<<< orphan*/  fb_image; int /*<<< orphan*/  pseudo_palette; struct qxl_device* qdev; } ;
struct qxl_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ visual; } ;
struct fb_info {struct fb_image const* pseudo_palette; TYPE_1__ fix; } ;
struct fb_image {int depth; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_MONO10 ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fb_image const*,int) ; 

__attribute__((used)) static void qxl_fb_image_init(struct qxl_fb_image *qxl_fb_image,
			      struct qxl_device *qdev, struct fb_info *info,
			      const struct fb_image *image)
{
	qxl_fb_image->qdev = qdev;
	if (info) {
		qxl_fb_image->visual = info->fix.visual;
		if (qxl_fb_image->visual == FB_VISUAL_TRUECOLOR ||
		    qxl_fb_image->visual == FB_VISUAL_DIRECTCOLOR)
			memcpy(&qxl_fb_image->pseudo_palette,
			       info->pseudo_palette,
			       sizeof(qxl_fb_image->pseudo_palette));
	} else {
		 /* fallback */
		if (image->depth == 1)
			qxl_fb_image->visual = FB_VISUAL_MONO10;
		else
			qxl_fb_image->visual = FB_VISUAL_DIRECTCOLOR;
	}
	if (image) {
		memcpy(&qxl_fb_image->fb_image, image,
		       sizeof(qxl_fb_image->fb_image));
	}
}