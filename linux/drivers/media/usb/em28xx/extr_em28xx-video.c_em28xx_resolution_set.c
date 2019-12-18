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
struct em28xx_v4l2 {int vbi_width; int norm; int vbi_height; int /*<<< orphan*/  vscale; int /*<<< orphan*/  hscale; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  em28xx_accumulator_set (struct em28xx*,int,int,int,int) ; 
 int /*<<< orphan*/  em28xx_capture_area_set (struct em28xx*,int /*<<< orphan*/ ,int,int,int) ; 
 int em28xx_scaler_set (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_set_outfmt (struct em28xx*) ; 
 int em28xx_vbi_supported (struct em28xx*) ; 
 int norm_maxh (struct em28xx*) ; 
 int norm_maxw (struct em28xx*) ; 

__attribute__((used)) static int em28xx_resolution_set(struct em28xx *dev)
{
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	int width = norm_maxw(dev);
	int height = norm_maxh(dev);

	/* Properly setup VBI */
	v4l2->vbi_width = 720;
	if (v4l2->norm & V4L2_STD_525_60)
		v4l2->vbi_height = 12;
	else
		v4l2->vbi_height = 18;

	em28xx_set_outfmt(dev);

	em28xx_accumulator_set(dev, 1, (width - 4) >> 2, 1, (height - 4) >> 2);

	/*
	 * If we don't set the start position to 2 in VBI mode, we end up
	 * with line 20/21 being YUYV encoded instead of being in 8-bit
	 * greyscale.  The core of the issue is that line 21 (and line 23 for
	 * PAL WSS) are inside of active video region, and as a result they
	 * get the pixelformatting associated with that area.  So by cropping
	 * it out, we end up with the same format as the rest of the VBI
	 * region
	 */
	if (em28xx_vbi_supported(dev) == 1)
		em28xx_capture_area_set(dev, 0, 2, width, height);
	else
		em28xx_capture_area_set(dev, 0, 0, width, height);

	return em28xx_scaler_set(dev, v4l2->hscale, v4l2->vscale);
}