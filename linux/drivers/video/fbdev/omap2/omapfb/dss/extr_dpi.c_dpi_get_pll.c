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
struct dss_pll {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
#define  OMAPDSS_VER_AM35xx 141 
#define  OMAPDSS_VER_AM43xx 140 
#define  OMAPDSS_VER_DRA7xx 139 
#define  OMAPDSS_VER_OMAP24xx 138 
#define  OMAPDSS_VER_OMAP34xx_ES1 137 
#define  OMAPDSS_VER_OMAP34xx_ES3 136 
#define  OMAPDSS_VER_OMAP3630 135 
#define  OMAPDSS_VER_OMAP4 134 
#define  OMAPDSS_VER_OMAP4430_ES1 133 
#define  OMAPDSS_VER_OMAP4430_ES2 132 
#define  OMAPDSS_VER_OMAP5 131 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 struct dss_pll* dss_pll_find (char*) ; 
 int omapdss_get_version () ; 

__attribute__((used)) static struct dss_pll *dpi_get_pll(enum omap_channel channel)
{
	/*
	 * XXX we can't currently use DSI PLL for DPI with OMAP3, as the DSI PLL
	 * would also be used for DISPC fclk. Meaning, when the DPI output is
	 * disabled, DISPC clock will be disabled, and TV out will stop.
	 */
	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP24xx:
	case OMAPDSS_VER_OMAP34xx_ES1:
	case OMAPDSS_VER_OMAP34xx_ES3:
	case OMAPDSS_VER_OMAP3630:
	case OMAPDSS_VER_AM35xx:
	case OMAPDSS_VER_AM43xx:
		return NULL;

	case OMAPDSS_VER_OMAP4430_ES1:
	case OMAPDSS_VER_OMAP4430_ES2:
	case OMAPDSS_VER_OMAP4:
		switch (channel) {
		case OMAP_DSS_CHANNEL_LCD:
			return dss_pll_find("dsi0");
		case OMAP_DSS_CHANNEL_LCD2:
			return dss_pll_find("dsi1");
		default:
			return NULL;
		}

	case OMAPDSS_VER_OMAP5:
		switch (channel) {
		case OMAP_DSS_CHANNEL_LCD:
			return dss_pll_find("dsi0");
		case OMAP_DSS_CHANNEL_LCD3:
			return dss_pll_find("dsi1");
		default:
			return NULL;
		}

	case OMAPDSS_VER_DRA7xx:
		switch (channel) {
		case OMAP_DSS_CHANNEL_LCD:
		case OMAP_DSS_CHANNEL_LCD2:
			return dss_pll_find("video0");
		case OMAP_DSS_CHANNEL_LCD3:
			return dss_pll_find("video1");
		default:
			return NULL;
		}

	default:
		return NULL;
	}
}