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
struct TYPE_4__ {unsigned int left; unsigned int width; unsigned int top; unsigned int height; } ;
struct TYPE_3__ {unsigned int width; unsigned int left; unsigned int height; unsigned int top; } ;
struct tpg_data {unsigned int src_width; unsigned int src_height; int vid_aspect; scalar_t__ pix_aspect; TYPE_2__ border; TYPE_1__ square; } ;

/* Variables and functions */
 scalar_t__ TPG_PIXEL_ASPECT_NTSC ; 
 scalar_t__ TPG_PIXEL_ASPECT_PAL ; 
#define  TPG_VIDEO_ASPECT_14X9_CENTRE 130 
 int TPG_VIDEO_ASPECT_16X9_ANAMORPHIC ; 
#define  TPG_VIDEO_ASPECT_16X9_CENTRE 129 
#define  TPG_VIDEO_ASPECT_4X3 128 

__attribute__((used)) static void tpg_calculate_square_border(struct tpg_data *tpg)
{
	unsigned w = tpg->src_width;
	unsigned h = tpg->src_height;
	unsigned sq_w, sq_h;

	sq_w = (w * 2 / 5) & ~1;
	if (((w - sq_w) / 2) & 1)
		sq_w += 2;
	sq_h = sq_w;
	tpg->square.width = sq_w;
	if (tpg->vid_aspect == TPG_VIDEO_ASPECT_16X9_ANAMORPHIC) {
		unsigned ana_sq_w = (sq_w / 4) * 3;

		if (((w - ana_sq_w) / 2) & 1)
			ana_sq_w += 2;
		tpg->square.width = ana_sq_w;
	}
	tpg->square.left = (w - tpg->square.width) / 2;
	if (tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC)
		sq_h = sq_w * 10 / 11;
	else if (tpg->pix_aspect == TPG_PIXEL_ASPECT_PAL)
		sq_h = sq_w * 59 / 54;
	tpg->square.height = sq_h;
	tpg->square.top = (h - sq_h) / 2;
	tpg->border.left = 0;
	tpg->border.width = w;
	tpg->border.top = 0;
	tpg->border.height = h;
	switch (tpg->vid_aspect) {
	case TPG_VIDEO_ASPECT_4X3:
		if (tpg->pix_aspect)
			return;
		if (3 * w >= 4 * h) {
			tpg->border.width = ((4 * h) / 3) & ~1;
			if (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			break;
		}
		tpg->border.height = ((3 * w) / 4) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		break;
	case TPG_VIDEO_ASPECT_14X9_CENTRE:
		if (tpg->pix_aspect) {
			tpg->border.height = tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC ? 420 : 506;
			tpg->border.top = (h - tpg->border.height) / 2;
			break;
		}
		if (9 * w >= 14 * h) {
			tpg->border.width = ((14 * h) / 9) & ~1;
			if (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			break;
		}
		tpg->border.height = ((9 * w) / 14) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		break;
	case TPG_VIDEO_ASPECT_16X9_CENTRE:
		if (tpg->pix_aspect) {
			tpg->border.height = tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC ? 368 : 442;
			tpg->border.top = (h - tpg->border.height) / 2;
			break;
		}
		if (9 * w >= 16 * h) {
			tpg->border.width = ((16 * h) / 9) & ~1;
			if (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			break;
		}
		tpg->border.height = ((9 * w) / 16) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		break;
	default:
		break;
	}
}