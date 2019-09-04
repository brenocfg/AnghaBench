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
struct TYPE_4__ {int* mX; unsigned long* clkout; } ;
struct dsi_clk_calc_ctx {int /*<<< orphan*/  req_pck_max; int /*<<< orphan*/  req_pck_min; TYPE_3__* dsi; TYPE_1__ dsi_cinfo; } ;
struct TYPE_6__ {TYPE_2__* dss; } ;
struct TYPE_5__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 size_t HSDIV_DISPC ; 
 int dispc_div_calc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dsi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  dsi_cm_calc_dispc_cb ; 

__attribute__((used)) static bool dsi_cm_calc_hsdiv_cb(int m_dispc, unsigned long dispc,
		void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	return dispc_div_calc(ctx->dsi->dss->dispc, dispc,
			      ctx->req_pck_min, ctx->req_pck_max,
			      dsi_cm_calc_dispc_cb, ctx);
}