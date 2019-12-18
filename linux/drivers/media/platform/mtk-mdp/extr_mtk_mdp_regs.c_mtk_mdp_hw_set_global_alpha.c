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
struct TYPE_8__ {TYPE_3__* global_alpha; } ;
struct TYPE_6__ {TYPE_1__* vsi; } ;
struct mtk_mdp_ctx {TYPE_4__ ctrls; TYPE_2__ vpu; } ;
struct mdp_config_misc {int /*<<< orphan*/  alpha; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_5__ {struct mdp_config_misc misc; } ;

/* Variables and functions */

void mtk_mdp_hw_set_global_alpha(struct mtk_mdp_ctx *ctx)
{
	struct mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->alpha = ctx->ctrls.global_alpha->val;
}