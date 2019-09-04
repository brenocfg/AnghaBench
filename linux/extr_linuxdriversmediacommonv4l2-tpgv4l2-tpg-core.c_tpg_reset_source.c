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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {unsigned int width; int height; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_3__ {unsigned int width; unsigned int height; scalar_t__ left; scalar_t__ top; } ;
struct tpg_data {unsigned int src_width; unsigned int src_height; unsigned int buf_height; unsigned int scaled_width; unsigned int planes; unsigned int* bytesperline; unsigned int* twopixelsize; int* hdownsampling; int recalc_square_border; TYPE_2__ compose; TYPE_1__ crop; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_HAS_T_OR_B (int /*<<< orphan*/ ) ; 

void tpg_reset_source(struct tpg_data *tpg, unsigned width, unsigned height,
		       u32 field)
{
	unsigned p;

	tpg->src_width = width;
	tpg->src_height = height;
	tpg->field = field;
	tpg->buf_height = height;
	if (V4L2_FIELD_HAS_T_OR_B(field))
		tpg->buf_height /= 2;
	tpg->scaled_width = width;
	tpg->crop.top = tpg->crop.left = 0;
	tpg->crop.width = width;
	tpg->crop.height = height;
	tpg->compose.top = tpg->compose.left = 0;
	tpg->compose.width = width;
	tpg->compose.height = tpg->buf_height;
	for (p = 0; p < tpg->planes; p++)
		tpg->bytesperline[p] = (width * tpg->twopixelsize[p]) /
				       (2 * tpg->hdownsampling[p]);
	tpg->recalc_square_border = true;
}