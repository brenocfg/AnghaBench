#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* vflip; TYPE_6__* hflip; TYPE_4__* rotate; } ;
struct TYPE_9__ {TYPE_2__* vsi; } ;
struct mtk_mdp_ctx {TYPE_5__ ctrls; TYPE_3__ vpu; } ;
struct mdp_config_misc {int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  orientation; } ;
struct TYPE_12__ {int /*<<< orphan*/  val; } ;
struct TYPE_10__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {struct mdp_config_misc misc; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */

void mtk_mdp_hw_set_rotation(struct mtk_mdp_ctx *ctx)
{
	struct mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->orientation = ctx->ctrls.rotate->val;
	misc->hflip = ctx->ctrls.hflip->val;
	misc->vflip = ctx->ctrls.vflip->val;
}