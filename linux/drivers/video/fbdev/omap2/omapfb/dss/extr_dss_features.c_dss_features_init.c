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
typedef  enum omapdss_version { ____Placeholder_omapdss_version } omapdss_version ;

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
 int /*<<< orphan*/  am35xx_dss_features ; 
 int /*<<< orphan*/  am43xx_dss_features ; 
 int /*<<< orphan*/  omap2_dss_features ; 
 int /*<<< orphan*/  omap3430_dss_features ; 
 int /*<<< orphan*/  omap3630_dss_features ; 
 int /*<<< orphan*/  omap4430_es1_0_dss_features ; 
 int /*<<< orphan*/  omap4430_es2_0_1_2_dss_features ; 
 int /*<<< orphan*/  omap4_dss_features ; 
 int /*<<< orphan*/  omap5_dss_features ; 
 int /*<<< orphan*/ * omap_current_dss_features ; 

void dss_features_init(enum omapdss_version version)
{
	switch (version) {
	case OMAPDSS_VER_OMAP24xx:
		omap_current_dss_features = &omap2_dss_features;
		break;

	case OMAPDSS_VER_OMAP34xx_ES1:
	case OMAPDSS_VER_OMAP34xx_ES3:
		omap_current_dss_features = &omap3430_dss_features;
		break;

	case OMAPDSS_VER_OMAP3630:
		omap_current_dss_features = &omap3630_dss_features;
		break;

	case OMAPDSS_VER_OMAP4430_ES1:
		omap_current_dss_features = &omap4430_es1_0_dss_features;
		break;

	case OMAPDSS_VER_OMAP4430_ES2:
		omap_current_dss_features = &omap4430_es2_0_1_2_dss_features;
		break;

	case OMAPDSS_VER_OMAP4:
		omap_current_dss_features = &omap4_dss_features;
		break;

	case OMAPDSS_VER_OMAP5:
	case OMAPDSS_VER_DRA7xx:
		omap_current_dss_features = &omap5_dss_features;
		break;

	case OMAPDSS_VER_AM35xx:
		omap_current_dss_features = &am35xx_dss_features;
		break;

	case OMAPDSS_VER_AM43xx:
		omap_current_dss_features = &am43xx_dss_features;
		break;

	default:
		DSSWARN("Unsupported OMAP version");
		break;
	}
}