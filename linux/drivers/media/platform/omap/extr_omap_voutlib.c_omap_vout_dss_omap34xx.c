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

/* Variables and functions */
#define  OMAPDSS_VER_AM35xx 131 
#define  OMAPDSS_VER_OMAP34xx_ES1 130 
#define  OMAPDSS_VER_OMAP34xx_ES3 129 
#define  OMAPDSS_VER_OMAP3630 128 
 int omapdss_get_version () ; 

bool omap_vout_dss_omap34xx(void)
{
	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP34xx_ES1:
	case OMAPDSS_VER_OMAP34xx_ES3:
	case OMAPDSS_VER_OMAP3630:
	case OMAPDSS_VER_AM35xx:
		return true;
	default:
		return false;
	}
}