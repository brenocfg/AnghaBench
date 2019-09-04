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
struct dpu_hw_cdm {TYPE_2__* hw_mdp; } ;
struct cdm_output_cfg {int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_cdm_output ) (TYPE_2__*,struct cdm_output_cfg*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct cdm_output_cfg*) ; 

__attribute__((used)) static void dpu_hw_cdm_disable(struct dpu_hw_cdm *ctx)
{
	struct cdm_output_cfg cdm_cfg = { 0 };

	if (ctx->hw_mdp && ctx->hw_mdp->ops.setup_cdm_output)
		ctx->hw_mdp->ops.setup_cdm_output(ctx->hw_mdp, &cdm_cfg);
}