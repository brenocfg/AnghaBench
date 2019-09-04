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
struct TYPE_7__ {TYPE_1__* hubp; struct dpp* dpp; } ;
struct pipe_ctx {int /*<<< orphan*/  pipe_idx; TYPE_3__ plane_res; } ;
struct dpp {TYPE_2__* funcs; int /*<<< orphan*/  inst; } ;
struct dce_hwseq {int dummy; } ;
struct dc {TYPE_4__* ctx; struct dce_hwseq* hwseq; } ;
struct TYPE_8__ {int /*<<< orphan*/  logger; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dpp_reset ) (struct dpp*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_IP_REQUEST_CNTL ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_REQUEST_EN ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpp_pg_control (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hubp_pg_control (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dpp*) ; 

__attribute__((used)) static void plane_atomic_power_down(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	struct dce_hwseq *hws = dc->hwseq;
	struct dpp *dpp = pipe_ctx->plane_res.dpp;
	DC_LOGGER_INIT(dc->ctx->logger);

	if (REG(DC_IP_REQUEST_CNTL)) {
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);
		dpp_pg_control(hws, dpp->inst, false);
		hubp_pg_control(hws, pipe_ctx->plane_res.hubp->inst, false);
		dpp->funcs->dpp_reset(dpp);
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Power gated front end %d\n", pipe_ctx->pipe_idx);
	}
}