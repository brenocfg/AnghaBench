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
struct vpfe_ccdc_black_clamp {int dc_sub; int sgain; int start_pixel; int sample_ln; int sample_pixel; int /*<<< orphan*/  enable; } ;
struct vpfe_ccdc {int dummy; } ;

/* Variables and functions */
 int VPFE_BLK_CLAMP_ENABLE ; 
 int VPFE_BLK_DC_SUB_MASK ; 
 int VPFE_BLK_SAMPLE_LINE_MASK ; 
 int VPFE_BLK_SAMPLE_LINE_SHIFT ; 
 int VPFE_BLK_SAMPLE_LN_MASK ; 
 int VPFE_BLK_SAMPLE_LN_SHIFT ; 
 int VPFE_BLK_SGAIN_MASK ; 
 int VPFE_BLK_ST_PXL_MASK ; 
 int VPFE_BLK_ST_PXL_SHIFT ; 
 int /*<<< orphan*/  VPFE_CLAMP ; 
 int VPFE_CLAMP_DEFAULT_VAL ; 
 int /*<<< orphan*/  VPFE_DCSUB ; 
 int VPFE_DCSUB_DEFAULT_VAL ; 
 int /*<<< orphan*/  vpfe_reg_write (struct vpfe_ccdc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vpfe_ccdc_config_black_clamp(struct vpfe_ccdc *ccdc,
			     struct vpfe_ccdc_black_clamp *bclamp)
{
	u32 val;

	if (!bclamp->enable) {
		/* configure DCSub */
		val = (bclamp->dc_sub) & VPFE_BLK_DC_SUB_MASK;
		vpfe_reg_write(ccdc, val, VPFE_DCSUB);
		vpfe_reg_write(ccdc, VPFE_CLAMP_DEFAULT_VAL, VPFE_CLAMP);
		return;
	}
	/*
	 * Configure gain,  Start pixel, No of line to be avg,
	 * No of pixel/line to be avg, & Enable the Black clamping
	 */
	val = ((bclamp->sgain & VPFE_BLK_SGAIN_MASK) |
	       ((bclamp->start_pixel & VPFE_BLK_ST_PXL_MASK) <<
		VPFE_BLK_ST_PXL_SHIFT) |
	       ((bclamp->sample_ln & VPFE_BLK_SAMPLE_LINE_MASK) <<
		VPFE_BLK_SAMPLE_LINE_SHIFT) |
	       ((bclamp->sample_pixel & VPFE_BLK_SAMPLE_LN_MASK) <<
		VPFE_BLK_SAMPLE_LN_SHIFT) | VPFE_BLK_CLAMP_ENABLE);
	vpfe_reg_write(ccdc, val, VPFE_CLAMP);
	/* If Black clamping is enable then make dcsub 0 */
	vpfe_reg_write(ccdc, VPFE_DCSUB_DEFAULT_VAL, VPFE_DCSUB);
}