#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  framedone_data; int /*<<< orphan*/  (* framedone_callback ) (int,int /*<<< orphan*/ ) ;scalar_t__ te_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_TIMING2 ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_enable_sidle () ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_perf_show (struct platform_device*,char*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_handle_framedone(struct platform_device *dsidev, int error)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	/* SIDLEMODE back to smart-idle */
	dispc_enable_sidle();

	if (dsi->te_enabled) {
		/* enable LP_RX_TO again after the TE */
		REG_FLD_MOD(dsidev, DSI_TIMING2, 1, 15, 15); /* LP_RX_TO */
	}

	dsi->framedone_callback(error, dsi->framedone_data);

	if (!error)
		dsi_perf_show(dsidev, "DISPC");
}