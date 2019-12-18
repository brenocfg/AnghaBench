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
struct TYPE_4__ {int enable; } ;
struct TYPE_3__ {int overlap_only; int global_alpha; int global_gain; int background_color_bpc; int top_gain; int bottom_inside_gain; int bottom_outside_gain; scalar_t__ bottom_gain_mode; } ;
struct mpcc {int mpcc_id; int dpp_id; TYPE_2__ sm_cfg; TYPE_1__ blnd_cfg; int /*<<< orphan*/ * mpcc_bot; } ;

/* Variables and functions */

__attribute__((used)) static void mpc2_init_mpcc(struct mpcc *mpcc, int mpcc_inst)
{
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = NULL;
	mpcc->blnd_cfg.overlap_only = false;
	mpcc->blnd_cfg.global_alpha = 0xff;
	mpcc->blnd_cfg.global_gain = 0xff;
	mpcc->blnd_cfg.background_color_bpc = 4;
	mpcc->blnd_cfg.bottom_gain_mode = 0;
	mpcc->blnd_cfg.top_gain = 0x1f000;
	mpcc->blnd_cfg.bottom_inside_gain = 0x1f000;
	mpcc->blnd_cfg.bottom_outside_gain = 0x1f000;
	mpcc->sm_cfg.enable = false;
}