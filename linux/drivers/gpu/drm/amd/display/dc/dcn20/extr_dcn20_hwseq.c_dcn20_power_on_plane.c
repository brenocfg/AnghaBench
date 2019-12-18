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
struct TYPE_7__ {TYPE_4__* hubp; TYPE_2__* dpp; } ;
struct pipe_ctx {TYPE_3__ plane_res; } ;
struct dce_hwseq {TYPE_1__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  inst; } ;
struct TYPE_6__ {int /*<<< orphan*/  inst; } ;
struct TYPE_5__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_IP_REQUEST_CNTL ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_REQUEST_EN ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcn20_dpp_pg_control (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcn20_hubp_pg_control (struct dce_hwseq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dcn20_power_on_plane(
	struct dce_hwseq *hws,
	struct pipe_ctx *pipe_ctx)
{
	DC_LOGGER_INIT(hws->ctx->logger);
	if (REG(DC_IP_REQUEST_CNTL)) {
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);
		dcn20_dpp_pg_control(hws, pipe_ctx->plane_res.dpp->inst, true);
		dcn20_hubp_pg_control(hws, pipe_ctx->plane_res.hubp->inst, true);
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Un-gated front end for pipe %d\n", pipe_ctx->plane_res.hubp->inst);
	}
}