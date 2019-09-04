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
typedef  int u16 ;
struct tinydrm_device {int dummy; } ;
struct mipi_dbi {int swap_bytes; int rotation; void* tx_buf; int /*<<< orphan*/  dc; int /*<<< orphan*/  enabled; } ;
struct drm_gem_cma_object {void* vaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {int width; int height; TYPE_3__* format; TYPE_2__ base; TYPE_1__* dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int x1; int x2; int y1; int y2; } ;
struct TYPE_6__ {scalar_t__ format; } ;
struct TYPE_4__ {struct tinydrm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  ILI9225_HORIZ_WINDOW_ADDR_1 ; 
 int /*<<< orphan*/  ILI9225_HORIZ_WINDOW_ADDR_2 ; 
 int /*<<< orphan*/  ILI9225_RAM_ADDRESS_SET_1 ; 
 int /*<<< orphan*/  ILI9225_RAM_ADDRESS_SET_2 ; 
 int /*<<< orphan*/  ILI9225_VERT_WINDOW_ADDR_1 ; 
 int /*<<< orphan*/  ILI9225_VERT_WINDOW_ADDR_2 ; 
 int /*<<< orphan*/  ILI9225_WRITE_DATA_TO_GRAM ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ili9225_command (struct mipi_dbi*,int /*<<< orphan*/ ,int) ; 
 int mipi_dbi_buf_copy (void*,struct drm_framebuffer*,struct drm_clip_rect*,int) ; 
 int mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,void*,int) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 int tinydrm_merge_clips (struct drm_clip_rect*,struct drm_clip_rect*,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static int ili9225_fb_dirty(struct drm_framebuffer *fb,
			    struct drm_file *file_priv, unsigned int flags,
			    unsigned int color, struct drm_clip_rect *clips,
			    unsigned int num_clips)
{
	struct drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	struct tinydrm_device *tdev = fb->dev->dev_private;
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);
	bool swap = mipi->swap_bytes;
	struct drm_clip_rect clip;
	u16 x_start, y_start;
	u16 x1, x2, y1, y2;
	int ret = 0;
	bool full;
	void *tr;

	if (!mipi->enabled)
		return 0;

	full = tinydrm_merge_clips(&clip, clips, num_clips, flags,
				   fb->width, fb->height);

	DRM_DEBUG("Flushing [FB:%d] x1=%u, x2=%u, y1=%u, y2=%u\n", fb->base.id,
		  clip.x1, clip.x2, clip.y1, clip.y2);

	if (!mipi->dc || !full || swap ||
	    fb->format->format == DRM_FORMAT_XRGB8888) {
		tr = mipi->tx_buf;
		ret = mipi_dbi_buf_copy(mipi->tx_buf, fb, &clip, swap);
		if (ret)
			return ret;
	} else {
		tr = cma_obj->vaddr;
	}

	switch (mipi->rotation) {
	default:
		x1 = clip.x1;
		x2 = clip.x2 - 1;
		y1 = clip.y1;
		y2 = clip.y2 - 1;
		x_start = x1;
		y_start = y1;
		break;
	case 90:
		x1 = clip.y1;
		x2 = clip.y2 - 1;
		y1 = fb->width - clip.x2;
		y2 = fb->width - clip.x1 - 1;
		x_start = x1;
		y_start = y2;
		break;
	case 180:
		x1 = fb->width - clip.x2;
		x2 = fb->width - clip.x1 - 1;
		y1 = fb->height - clip.y2;
		y2 = fb->height - clip.y1 - 1;
		x_start = x2;
		y_start = y2;
		break;
	case 270:
		x1 = fb->height - clip.y2;
		x2 = fb->height - clip.y1 - 1;
		y1 = clip.x1;
		y2 = clip.x2 - 1;
		x_start = x2;
		y_start = y1;
		break;
	}

	ili9225_command(mipi, ILI9225_HORIZ_WINDOW_ADDR_1, x2);
	ili9225_command(mipi, ILI9225_HORIZ_WINDOW_ADDR_2, x1);
	ili9225_command(mipi, ILI9225_VERT_WINDOW_ADDR_1, y2);
	ili9225_command(mipi, ILI9225_VERT_WINDOW_ADDR_2, y1);

	ili9225_command(mipi, ILI9225_RAM_ADDRESS_SET_1, x_start);
	ili9225_command(mipi, ILI9225_RAM_ADDRESS_SET_2, y_start);

	ret = mipi_dbi_command_buf(mipi, ILI9225_WRITE_DATA_TO_GRAM, tr,
				(clip.x2 - clip.x1) * (clip.y2 - clip.y1) * 2);

	return ret;
}