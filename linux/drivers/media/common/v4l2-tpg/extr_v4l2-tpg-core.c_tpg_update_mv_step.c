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
struct tpg_data {int mv_hor_mode; int mv_hor_step; int src_width; int mv_vert_mode; int mv_vert_step; int src_height; scalar_t__ hflip; } ;

/* Variables and functions */
#define  TPG_MOVE_NEG 134 
#define  TPG_MOVE_NEG_FAST 133 
#define  TPG_MOVE_NEG_SLOW 132 
#define  TPG_MOVE_NONE 131 
#define  TPG_MOVE_POS 130 
#define  TPG_MOVE_POS_FAST 129 
#define  TPG_MOVE_POS_SLOW 128 

void tpg_update_mv_step(struct tpg_data *tpg)
{
	int factor = tpg->mv_hor_mode > TPG_MOVE_NONE ? -1 : 1;

	if (tpg->hflip)
		factor = -factor;
	switch (tpg->mv_hor_mode) {
	case TPG_MOVE_NEG_FAST:
	case TPG_MOVE_POS_FAST:
		tpg->mv_hor_step = ((tpg->src_width + 319) / 320) * 4;
		break;
	case TPG_MOVE_NEG:
	case TPG_MOVE_POS:
		tpg->mv_hor_step = ((tpg->src_width + 639) / 640) * 4;
		break;
	case TPG_MOVE_NEG_SLOW:
	case TPG_MOVE_POS_SLOW:
		tpg->mv_hor_step = 2;
		break;
	case TPG_MOVE_NONE:
		tpg->mv_hor_step = 0;
		break;
	}
	if (factor < 0)
		tpg->mv_hor_step = tpg->src_width - tpg->mv_hor_step;

	factor = tpg->mv_vert_mode > TPG_MOVE_NONE ? -1 : 1;
	switch (tpg->mv_vert_mode) {
	case TPG_MOVE_NEG_FAST:
	case TPG_MOVE_POS_FAST:
		tpg->mv_vert_step = ((tpg->src_width + 319) / 320) * 4;
		break;
	case TPG_MOVE_NEG:
	case TPG_MOVE_POS:
		tpg->mv_vert_step = ((tpg->src_width + 639) / 640) * 4;
		break;
	case TPG_MOVE_NEG_SLOW:
	case TPG_MOVE_POS_SLOW:
		tpg->mv_vert_step = 1;
		break;
	case TPG_MOVE_NONE:
		tpg->mv_vert_step = 0;
		break;
	}
	if (factor < 0)
		tpg->mv_vert_step = tpg->src_height - tpg->mv_vert_step;
}