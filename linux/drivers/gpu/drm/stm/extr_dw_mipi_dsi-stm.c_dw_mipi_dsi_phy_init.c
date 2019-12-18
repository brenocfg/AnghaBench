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
typedef  int u32 ;
struct dw_mipi_dsi_stm {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ DSI_WISR ; 
 int /*<<< orphan*/  DSI_WRPCR ; 
 int /*<<< orphan*/  SLEEP_US ; 
 int /*<<< orphan*/  TIMEOUT_US ; 
 int WISR_PLLLS ; 
 int WISR_RRS ; 
 int WRPCR_BGREN ; 
 int WRPCR_PLLEN ; 
 int WRPCR_REGEN ; 
 int /*<<< orphan*/  dsi_set (struct dw_mipi_dsi_stm*,int /*<<< orphan*/ ,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_phy_init(void *priv_data)
{
	struct dw_mipi_dsi_stm *dsi = priv_data;
	u32 val;
	int ret;

	/* Enable the regulator */
	dsi_set(dsi, DSI_WRPCR, WRPCR_REGEN | WRPCR_BGREN);
	ret = readl_poll_timeout(dsi->base + DSI_WISR, val, val & WISR_RRS,
				 SLEEP_US, TIMEOUT_US);
	if (ret)
		DRM_DEBUG_DRIVER("!TIMEOUT! waiting REGU, let's continue\n");

	/* Enable the DSI PLL & wait for its lock */
	dsi_set(dsi, DSI_WRPCR, WRPCR_PLLEN);
	ret = readl_poll_timeout(dsi->base + DSI_WISR, val, val & WISR_PLLLS,
				 SLEEP_US, TIMEOUT_US);
	if (ret)
		DRM_DEBUG_DRIVER("!TIMEOUT! waiting PLL, let's continue\n");

	return 0;
}