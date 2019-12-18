#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dsi_data {int /*<<< orphan*/  framedone_data; int /*<<< orphan*/  (* framedone_callback ) (int,int /*<<< orphan*/ ) ;scalar_t__ te_enabled; TYPE_1__* dss; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_TIMING2 ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_enable_sidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_perf_show (struct dsi_data*,char*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_handle_framedone(struct dsi_data *dsi, int error)
{
	/* SIDLEMODE back to smart-idle */
	dispc_enable_sidle(dsi->dss->dispc);

	if (dsi->te_enabled) {
		/* enable LP_RX_TO again after the TE */
		REG_FLD_MOD(dsi, DSI_TIMING2, 1, 15, 15); /* LP_RX_TO */
	}

	dsi->framedone_callback(error, dsi->framedone_data);

	if (!error)
		dsi_perf_show(dsi, "DISPC");
}