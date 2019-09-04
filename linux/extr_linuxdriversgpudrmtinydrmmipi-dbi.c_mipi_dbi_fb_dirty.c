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
struct tinydrm_device {int dummy; } ;
struct mipi_dbi {int swap_bytes; void* tx_buf; int /*<<< orphan*/  dc; int /*<<< orphan*/  enabled; } ;
struct drm_gem_cma_object {void* vaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_3__* format; TYPE_2__ base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int x1; int x2; int y1; int y2; } ;
struct TYPE_6__ {scalar_t__ format; } ;
struct TYPE_4__ {struct tinydrm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  MIPI_DCS_SET_COLUMN_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PAGE_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int mipi_dbi_buf_copy (void*,struct drm_framebuffer*,struct drm_clip_rect*,int) ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,void*,int) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 int tinydrm_merge_clips (struct drm_clip_rect*,struct drm_clip_rect*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipi_dbi_fb_dirty(struct drm_framebuffer *fb,
			     struct drm_file *file_priv,
			     unsigned int flags, unsigned int color,
			     struct drm_clip_rect *clips,
			     unsigned int num_clips)
{
	struct drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	struct tinydrm_device *tdev = fb->dev->dev_private;
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);
	bool swap = mipi->swap_bytes;
	struct drm_clip_rect clip;
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

	mipi_dbi_command(mipi, MIPI_DCS_SET_COLUMN_ADDRESS,
			 (clip.x1 >> 8) & 0xFF, clip.x1 & 0xFF,
			 (clip.x2 >> 8) & 0xFF, (clip.x2 - 1) & 0xFF);
	mipi_dbi_command(mipi, MIPI_DCS_SET_PAGE_ADDRESS,
			 (clip.y1 >> 8) & 0xFF, clip.y1 & 0xFF,
			 (clip.y2 >> 8) & 0xFF, (clip.y2 - 1) & 0xFF);

	ret = mipi_dbi_command_buf(mipi, MIPI_DCS_WRITE_MEMORY_START, tr,
				(clip.x2 - clip.x1) * (clip.y2 - clip.y1) * 2);

	return ret;
}