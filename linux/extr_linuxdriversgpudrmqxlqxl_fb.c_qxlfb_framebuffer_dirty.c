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
struct TYPE_6__ {int* pitches; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct qxl_fbdev {scalar_t__ shadow; TYPE_3__ qfb; } ;
struct TYPE_8__ {int /*<<< orphan*/ * transp; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; scalar_t__ len; scalar_t__ start; } ;
struct fb_image {int dx; int dy; int fg_color; int depth; scalar_t__ data; TYPE_4__ cmap; scalar_t__ bg_color; scalar_t__ height; scalar_t__ width; } ;
struct qxl_fb_image {struct fb_image fb_image; } ;
struct qxl_device {struct fb_info* fbdev_info; } ;
struct fb_info {struct qxl_fbdev* par; } ;
struct drm_framebuffer {TYPE_1__* dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int x1; int y1; scalar_t__ y2; scalar_t__ x2; } ;
struct TYPE_5__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_draw_opaque_fb (struct qxl_fb_image*,int) ; 
 int /*<<< orphan*/  qxl_fb_image_init (struct qxl_fb_image*,struct qxl_device*,struct fb_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qxlfb_framebuffer_dirty(struct drm_framebuffer *fb,
				   struct drm_file *file_priv,
				   unsigned flags, unsigned color,
				   struct drm_clip_rect *clips,
				   unsigned num_clips)
{
	struct qxl_device *qdev = fb->dev->dev_private;
	struct fb_info *info = qdev->fbdev_info;
	struct qxl_fbdev *qfbdev = info->par;
	struct qxl_fb_image qxl_fb_image;
	struct fb_image *image = &qxl_fb_image.fb_image;

	/* TODO: hard coding 32 bpp */
	int stride = qfbdev->qfb.base.pitches[0];

	/*
	 * we are using a shadow draw buffer, at qdev->surface0_shadow
	 */
	image->dx = clips->x1;
	image->dy = clips->y1;
	image->width = clips->x2 - clips->x1;
	image->height = clips->y2 - clips->y1;
	image->fg_color = 0xffffffff; /* unused, just to avoid uninitialized
					 warnings */
	image->bg_color = 0;
	image->depth = 32;	     /* TODO: take from somewhere? */
	image->cmap.start = 0;
	image->cmap.len = 0;
	image->cmap.red = NULL;
	image->cmap.green = NULL;
	image->cmap.blue = NULL;
	image->cmap.transp = NULL;
	image->data = qfbdev->shadow + (clips->x1 * 4) + (stride * clips->y1);

	qxl_fb_image_init(&qxl_fb_image, qdev, info, NULL);
	qxl_draw_opaque_fb(&qxl_fb_image, stride);

	return 0;
}