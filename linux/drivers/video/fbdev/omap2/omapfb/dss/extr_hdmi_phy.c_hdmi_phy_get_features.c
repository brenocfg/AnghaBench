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
struct hdmi_phy_features {int dummy; } ;

/* Variables and functions */
#define  OMAPDSS_VER_DRA7xx 132 
#define  OMAPDSS_VER_OMAP4 131 
#define  OMAPDSS_VER_OMAP4430_ES1 130 
#define  OMAPDSS_VER_OMAP4430_ES2 129 
#define  OMAPDSS_VER_OMAP5 128 
 struct hdmi_phy_features const omap44xx_phy_feats ; 
 struct hdmi_phy_features const omap54xx_phy_feats ; 
 int omapdss_get_version () ; 

__attribute__((used)) static const struct hdmi_phy_features *hdmi_phy_get_features(void)
{
	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP4430_ES1:
	case OMAPDSS_VER_OMAP4430_ES2:
	case OMAPDSS_VER_OMAP4:
		return &omap44xx_phy_feats;

	case OMAPDSS_VER_OMAP5:
	case OMAPDSS_VER_DRA7xx:
		return &omap54xx_phy_feats;

	default:
		return NULL;
	}
}