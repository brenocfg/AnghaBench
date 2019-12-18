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
struct dw_mipi_dsi_stm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DSI_WCR ; 
 int /*<<< orphan*/  WCR_DSIEN ; 
 int /*<<< orphan*/  dsi_clear (struct dw_mipi_dsi_stm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_phy_power_off(void *priv_data)
{
	struct dw_mipi_dsi_stm *dsi = priv_data;

	DRM_DEBUG_DRIVER("\n");

	/* Disable the DSI wrapper */
	dsi_clear(dsi, DSI_WCR, WCR_DSIEN);
}