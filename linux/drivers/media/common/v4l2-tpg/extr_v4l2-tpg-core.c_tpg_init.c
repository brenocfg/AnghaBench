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
struct TYPE_4__ {unsigned int width; unsigned int height; } ;
struct TYPE_3__ {unsigned int width; unsigned int height; } ;
struct tpg_data {unsigned int scaled_width; unsigned int src_width; unsigned int src_height; unsigned int buf_height; int recalc_colors; int recalc_square_border; int brightness; int contrast; int saturation; int perc_fill; int /*<<< orphan*/  hsv_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; void* mv_vert_mode; void* mv_hor_mode; scalar_t__ hue; TYPE_2__ compose; TYPE_1__ crop; } ;

/* Variables and functions */
 void* TPG_MOVE_NONE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_HSV_ENC_180 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  memset (struct tpg_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpg_s_fourcc (struct tpg_data*,int /*<<< orphan*/ ) ; 

void tpg_init(struct tpg_data *tpg, unsigned w, unsigned h)
{
	memset(tpg, 0, sizeof(*tpg));
	tpg->scaled_width = tpg->src_width = w;
	tpg->src_height = tpg->buf_height = h;
	tpg->crop.width = tpg->compose.width = w;
	tpg->crop.height = tpg->compose.height = h;
	tpg->recalc_colors = true;
	tpg->recalc_square_border = true;
	tpg->brightness = 128;
	tpg->contrast = 128;
	tpg->saturation = 128;
	tpg->hue = 0;
	tpg->mv_hor_mode = TPG_MOVE_NONE;
	tpg->mv_vert_mode = TPG_MOVE_NONE;
	tpg->field = V4L2_FIELD_NONE;
	tpg_s_fourcc(tpg, V4L2_PIX_FMT_RGB24);
	tpg->colorspace = V4L2_COLORSPACE_SRGB;
	tpg->perc_fill = 100;
	tpg->hsv_enc = V4L2_HSV_ENC_180;
}