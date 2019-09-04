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
typedef  int u32 ;
struct ccdc_black_clamp {int dc_sub; int sgain; int start_pixel; int sample_ln; int sample_pixel; int /*<<< orphan*/  enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CCDC_BLK_CLAMP_ENABLE ; 
 int CCDC_BLK_DC_SUB_MASK ; 
 int CCDC_BLK_SAMPLE_LINE_MASK ; 
 int CCDC_BLK_SAMPLE_LINE_SHIFT ; 
 int CCDC_BLK_SAMPLE_LN_MASK ; 
 int CCDC_BLK_SAMPLE_LN_SHIFT ; 
 int CCDC_BLK_SGAIN_MASK ; 
 int CCDC_BLK_ST_PXL_MASK ; 
 int CCDC_BLK_ST_PXL_SHIFT ; 
 int /*<<< orphan*/  CCDC_CLAMP ; 
 int CCDC_CLAMP_DEFAULT_VAL ; 
 int /*<<< orphan*/  CCDC_DCSUB ; 
 int CCDC_DCSUB_DEFAULT_VAL ; 
 TYPE_1__ ccdc_cfg ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_black_clamp(struct ccdc_black_clamp *bclamp)
{
	u32 val;

	if (!bclamp->enable) {
		/* configure DCSub */
		val = (bclamp->dc_sub) & CCDC_BLK_DC_SUB_MASK;
		regw(val, CCDC_DCSUB);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to DCSUB...\n", val);
		regw(CCDC_CLAMP_DEFAULT_VAL, CCDC_CLAMP);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x0000 to CLAMP...\n");
		return;
	}
	/*
	 * Configure gain,  Start pixel, No of line to be avg,
	 * No of pixel/line to be avg, & Enable the Black clamping
	 */
	val = ((bclamp->sgain & CCDC_BLK_SGAIN_MASK) |
	       ((bclamp->start_pixel & CCDC_BLK_ST_PXL_MASK) <<
		CCDC_BLK_ST_PXL_SHIFT) |
	       ((bclamp->sample_ln & CCDC_BLK_SAMPLE_LINE_MASK) <<
		CCDC_BLK_SAMPLE_LINE_SHIFT) |
	       ((bclamp->sample_pixel & CCDC_BLK_SAMPLE_LN_MASK) <<
		CCDC_BLK_SAMPLE_LN_SHIFT) | CCDC_BLK_CLAMP_ENABLE);
	regw(val, CCDC_CLAMP);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to CLAMP...\n", val);
	/* If Black clamping is enable then make dcsub 0 */
	regw(CCDC_DCSUB_DEFAULT_VAL, CCDC_DCSUB);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x00000000 to DCSUB...\n");
}