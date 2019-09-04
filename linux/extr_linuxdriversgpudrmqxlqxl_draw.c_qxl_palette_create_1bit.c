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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct qxl_release {int dummy; } ;
struct qxl_palette {int num_ents; scalar_t__* ents; scalar_t__ unique; } ;
struct fb_image {size_t fg_color; size_t bg_color; } ;
struct qxl_fb_image {scalar_t__ visual; scalar_t__* pseudo_palette; struct fb_image fb_image; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int qxl_bo_kmap (struct qxl_bo*,void**) ; 
 int /*<<< orphan*/  qxl_bo_kunmap (struct qxl_bo*) ; 

__attribute__((used)) static int qxl_palette_create_1bit(struct qxl_bo *palette_bo,
				   struct qxl_release *release,
				   const struct qxl_fb_image *qxl_fb_image)
{
	const struct fb_image *fb_image = &qxl_fb_image->fb_image;
	uint32_t visual = qxl_fb_image->visual;
	const uint32_t *pseudo_palette = qxl_fb_image->pseudo_palette;
	struct qxl_palette *pal;
	int ret;
	uint32_t fgcolor, bgcolor;
	static uint64_t unique; /* we make no attempt to actually set this
				 * correctly globaly, since that would require
				 * tracking all of our palettes. */
	ret = qxl_bo_kmap(palette_bo, (void **)&pal);
	if (ret)
		return ret;
	pal->num_ents = 2;
	pal->unique = unique++;
	if (visual == FB_VISUAL_TRUECOLOR || visual == FB_VISUAL_DIRECTCOLOR) {
		/* NB: this is the only used branch currently. */
		fgcolor = pseudo_palette[fb_image->fg_color];
		bgcolor = pseudo_palette[fb_image->bg_color];
	} else {
		fgcolor = fb_image->fg_color;
		bgcolor = fb_image->bg_color;
	}
	pal->ents[0] = bgcolor;
	pal->ents[1] = fgcolor;
	qxl_bo_kunmap(palette_bo);
	return 0;
}