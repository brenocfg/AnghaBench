#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x; int width; int y; int height; } ;
struct scaler_data {int h_active; int v_active; TYPE_5__ recout; } ;
struct TYPE_9__ {TYPE_3__* ctx; } ;
struct dce_transform {TYPE_4__ base; } ;
struct TYPE_8__ {TYPE_2__* dc; } ;
struct TYPE_6__ {scalar_t__ visual_confirm; } ;
struct TYPE_7__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  EXT_OVERSCAN_BOTTOM ; 
 int /*<<< orphan*/  EXT_OVERSCAN_LEFT ; 
 int /*<<< orphan*/  EXT_OVERSCAN_LEFT_RIGHT ; 
 int /*<<< orphan*/  EXT_OVERSCAN_RIGHT ; 
 int /*<<< orphan*/  EXT_OVERSCAN_TOP ; 
 int /*<<< orphan*/  EXT_OVERSCAN_TOP_BOTTOM ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VISUAL_CONFIRM_DISABLE ; 

__attribute__((used)) static void program_overscan(
		struct dce_transform *xfm_dce,
		const struct scaler_data *data)
{
	int overscan_right = data->h_active
			- data->recout.x - data->recout.width;
	int overscan_bottom = data->v_active
			- data->recout.y - data->recout.height;

	if (xfm_dce->base.ctx->dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE) {
		overscan_bottom += 2;
		overscan_right += 2;
	}

	if (overscan_right < 0) {
		BREAK_TO_DEBUGGER();
		overscan_right = 0;
	}
	if (overscan_bottom < 0) {
		BREAK_TO_DEBUGGER();
		overscan_bottom = 0;
	}

	REG_SET_2(EXT_OVERSCAN_LEFT_RIGHT, 0,
			EXT_OVERSCAN_LEFT, data->recout.x,
			EXT_OVERSCAN_RIGHT, overscan_right);
	REG_SET_2(EXT_OVERSCAN_TOP_BOTTOM, 0,
			EXT_OVERSCAN_TOP, data->recout.y,
			EXT_OVERSCAN_BOTTOM, overscan_bottom);
}