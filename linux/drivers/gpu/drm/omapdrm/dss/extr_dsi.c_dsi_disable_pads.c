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
struct dsi_data {TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ model; } ;

/* Variables and functions */
 scalar_t__ DSI_MODEL_OMAP4 ; 
 scalar_t__ DSI_MODEL_OMAP5 ; 
 int /*<<< orphan*/  dsi_omap4_mux_pads (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_omap5_mux_pads (struct dsi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_disable_pads(struct dsi_data *dsi)
{
	if (dsi->data->model == DSI_MODEL_OMAP4)
		dsi_omap4_mux_pads(dsi, 0);
	else if (dsi->data->model == DSI_MODEL_OMAP5)
		dsi_omap5_mux_pads(dsi, 0);
}