#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum vpss_ccdc_source_sel { ____Placeholder_vpss_ccdc_source_sel } vpss_ccdc_source_sel ;
struct TYPE_3__ {int /*<<< orphan*/  config_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ bayer; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPSS_BL_CLOCK ; 
 int VPSS_CCDCIN ; 
 int /*<<< orphan*/  VPSS_CCDC_CLOCK ; 
 int /*<<< orphan*/  VPSS_IPIPEIF_CLOCK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ isif_cfg ; 
 int /*<<< orphan*/  isif_config_defaults ; 
 int /*<<< orphan*/  isif_config_gain_offset () ; 
 int /*<<< orphan*/  vpss_enable_clock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vpss_select_ccdc_source (int) ; 

__attribute__((used)) static void isif_restore_defaults(void)
{
	enum vpss_ccdc_source_sel source = VPSS_CCDCIN;

	dev_dbg(isif_cfg.dev, "\nstarting isif_restore_defaults...");
	isif_cfg.bayer.config_params = isif_config_defaults;
	/* Enable clock to ISIF, IPIPEIF and BL */
	vpss_enable_clock(VPSS_CCDC_CLOCK, 1);
	vpss_enable_clock(VPSS_IPIPEIF_CLOCK, 1);
	vpss_enable_clock(VPSS_BL_CLOCK, 1);
	/* Set default offset and gain */
	isif_config_gain_offset();
	vpss_select_ccdc_source(source);
	dev_dbg(isif_cfg.dev, "\nEnd of isif_restore_defaults...");
}