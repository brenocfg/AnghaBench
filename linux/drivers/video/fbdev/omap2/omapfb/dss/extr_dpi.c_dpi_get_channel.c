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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*) ; 
#define  OMAPDSS_VER_AM35xx 138 
#define  OMAPDSS_VER_AM43xx 137 
#define  OMAPDSS_VER_DRA7xx 136 
#define  OMAPDSS_VER_OMAP24xx 135 
#define  OMAPDSS_VER_OMAP34xx_ES1 134 
#define  OMAPDSS_VER_OMAP34xx_ES3 133 
#define  OMAPDSS_VER_OMAP3630 132 
#define  OMAPDSS_VER_OMAP4 131 
#define  OMAPDSS_VER_OMAP4430_ES1 130 
#define  OMAPDSS_VER_OMAP4430_ES2 129 
#define  OMAPDSS_VER_OMAP5 128 
 int OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 
 int omapdss_get_version () ; 

__attribute__((used)) static enum omap_channel dpi_get_channel(int port_num)
{
	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP24xx:
	case OMAPDSS_VER_OMAP34xx_ES1:
	case OMAPDSS_VER_OMAP34xx_ES3:
	case OMAPDSS_VER_OMAP3630:
	case OMAPDSS_VER_AM35xx:
	case OMAPDSS_VER_AM43xx:
		return OMAP_DSS_CHANNEL_LCD;

	case OMAPDSS_VER_DRA7xx:
		switch (port_num) {
		case 2:
			return OMAP_DSS_CHANNEL_LCD3;
		case 1:
			return OMAP_DSS_CHANNEL_LCD2;
		case 0:
		default:
			return OMAP_DSS_CHANNEL_LCD;
		}

	case OMAPDSS_VER_OMAP4430_ES1:
	case OMAPDSS_VER_OMAP4430_ES2:
	case OMAPDSS_VER_OMAP4:
		return OMAP_DSS_CHANNEL_LCD2;

	case OMAPDSS_VER_OMAP5:
		return OMAP_DSS_CHANNEL_LCD3;

	default:
		DSSWARN("unsupported DSS version\n");
		return OMAP_DSS_CHANNEL_LCD;
	}
}