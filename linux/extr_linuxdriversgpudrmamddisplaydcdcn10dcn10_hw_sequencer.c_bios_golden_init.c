#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dc_bios {TYPE_3__* funcs; } ;
struct dc {TYPE_2__* res_pool; TYPE_1__* ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable_disp_power_gating ) (struct dc_bios*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int pipe_count; } ;
struct TYPE_4__ {struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_PIPE_DISABLE ; 
 int /*<<< orphan*/  ASIC_PIPE_INIT ; 
 scalar_t__ CONTROLLER_ID_D0 ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dc_bios*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bios_golden_init(struct dc *dc)
{
	struct dc_bios *bp = dc->ctx->dc_bios;
	int i;

	/* initialize dcn global */
	bp->funcs->enable_disp_power_gating(bp,
			CONTROLLER_ID_D0, ASIC_PIPE_INIT);

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		/* initialize dcn per pipe */
		bp->funcs->enable_disp_power_gating(bp,
				CONTROLLER_ID_D0 + i, ASIC_PIPE_DISABLE);
	}
}