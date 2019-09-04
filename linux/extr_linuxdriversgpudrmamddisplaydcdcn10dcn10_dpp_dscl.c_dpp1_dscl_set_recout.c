#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rect {scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int inst; TYPE_3__* ctx; } ;
struct dcn10_dpp {TYPE_4__ base; } ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_5__ {scalar_t__ visual_confirm; } ;
struct TYPE_6__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECOUT_HEIGHT ; 
 int /*<<< orphan*/  RECOUT_SIZE ; 
 int /*<<< orphan*/  RECOUT_START ; 
 int /*<<< orphan*/  RECOUT_START_X ; 
 int /*<<< orphan*/  RECOUT_START_Y ; 
 int /*<<< orphan*/  RECOUT_WIDTH ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ VISUAL_CONFIRM_DISABLE ; 

__attribute__((used)) static void dpp1_dscl_set_recout(
			struct dcn10_dpp *dpp, const struct rect *recout)
{
	int visual_confirm_on = 0;
	if (dpp->base.ctx->dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE)
		visual_confirm_on = 1;

	REG_SET_2(RECOUT_START, 0,
		/* First pixel of RECOUT */
			 RECOUT_START_X, recout->x,
		/* First line of RECOUT */
			 RECOUT_START_Y, recout->y);

	REG_SET_2(RECOUT_SIZE, 0,
		/* Number of RECOUT horizontal pixels */
			 RECOUT_WIDTH, recout->width,
		/* Number of RECOUT vertical lines */
			 RECOUT_HEIGHT, recout->height
			 - visual_confirm_on * 4 * (dpp->base.inst + 1));
}