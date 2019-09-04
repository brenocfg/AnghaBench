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
typedef  int /*<<< orphan*/  u8 ;
struct tinydrm_device {int dummy; } ;
struct mipi_dbi {scalar_t__ tx_buf; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_2__ base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* dev; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int x1; int x2; int y1; int y2; } ;
struct TYPE_3__ {struct tinydrm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  MIPI_DCS_SET_COLUMN_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PAGE_ADDRESS ; 
 int /*<<< orphan*/  MIPI_DCS_WRITE_MEMORY_START ; 
 int /*<<< orphan*/  mipi_dbi_command (struct mipi_dbi*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int mipi_dbi_command_buf (struct mipi_dbi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mipi_dbi* mipi_dbi_from_tinydrm (struct tinydrm_device*) ; 
 int rounddown (int,int) ; 
 int roundup (int,int) ; 
 int st7586_buf_copy (scalar_t__,struct drm_framebuffer*,struct drm_clip_rect*) ; 
 int /*<<< orphan*/  tinydrm_merge_clips (struct drm_clip_rect*,struct drm_clip_rect*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st7586_fb_dirty(struct drm_framebuffer *fb,
			   struct drm_file *file_priv, unsigned int flags,
			   unsigned int color, struct drm_clip_rect *clips,
			   unsigned int num_clips)
{
	struct tinydrm_device *tdev = fb->dev->dev_private;
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);
	struct drm_clip_rect clip;
	int start, end;
	int ret = 0;

	if (!mipi->enabled)
		return 0;

	tinydrm_merge_clips(&clip, clips, num_clips, flags, fb->width,
			    fb->height);

	/* 3 pixels per byte, so grow clip to nearest multiple of 3 */
	clip.x1 = rounddown(clip.x1, 3);
	clip.x2 = roundup(clip.x2, 3);

	DRM_DEBUG("Flushing [FB:%d] x1=%u, x2=%u, y1=%u, y2=%u\n", fb->base.id,
		  clip.x1, clip.x2, clip.y1, clip.y2);

	ret = st7586_buf_copy(mipi->tx_buf, fb, &clip);
	if (ret)
		return ret;

	/* Pixels are packed 3 per byte */
	start = clip.x1 / 3;
	end = clip.x2 / 3;

	mipi_dbi_command(mipi, MIPI_DCS_SET_COLUMN_ADDRESS,
			 (start >> 8) & 0xFF, start & 0xFF,
			 (end >> 8) & 0xFF, (end - 1) & 0xFF);
	mipi_dbi_command(mipi, MIPI_DCS_SET_PAGE_ADDRESS,
			 (clip.y1 >> 8) & 0xFF, clip.y1 & 0xFF,
			 (clip.y2 >> 8) & 0xFF, (clip.y2 - 1) & 0xFF);

	ret = mipi_dbi_command_buf(mipi, MIPI_DCS_WRITE_MEMORY_START,
				   (u8 *)mipi->tx_buf,
				   (end - start) * (clip.y2 - clip.y1));

	return ret;
}