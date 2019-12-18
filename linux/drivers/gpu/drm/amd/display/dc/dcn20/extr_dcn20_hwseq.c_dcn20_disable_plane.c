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
struct TYPE_6__ {TYPE_2__* hubp; } ;
struct pipe_ctx {int /*<<< orphan*/  pipe_idx; TYPE_3__ plane_res; } ;
struct dc {TYPE_1__* ctx; } ;
struct TYPE_5__ {scalar_t__ power_gated; } ;
struct TYPE_4__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcn20_plane_atomic_disable (struct dc*,struct pipe_ctx*) ; 

void dcn20_disable_plane(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	DC_LOGGER_INIT(dc->ctx->logger);

	if (!pipe_ctx->plane_res.hubp || pipe_ctx->plane_res.hubp->power_gated)
		return;

	dcn20_plane_atomic_disable(dc, pipe_ctx);

	DC_LOG_DC("Power down front end %d\n",
					pipe_ctx->pipe_idx);
}