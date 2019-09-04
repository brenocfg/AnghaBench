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
struct ccdc_black_clamp {int dc_sub; int start_pixel; int sample_pixel; int sample_ln; int /*<<< orphan*/  b_clamp_enable; } ;

/* Variables and functions */
 int CCDC_BLK_CLAMP_ENABLE ; 
 int CCDC_BLK_DC_SUB_MASK ; 
 int CCDC_BLK_SAMPLE_LN_MASK ; 
 int CCDC_BLK_SAMPLE_LN_SHIFT ; 
 int CCDC_BLK_ST_PXL_MASK ; 
 int CCDC_NUM_LINE_CALC_MASK ; 
 int CCDC_NUM_LINE_CALC_SHIFT ; 
 int /*<<< orphan*/  CLAMP ; 
 int /*<<< orphan*/  DCSUB ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_black_clamp(struct ccdc_black_clamp *bclamp)
{
	u32 val;

	if (!bclamp->b_clamp_enable) {
		/* configure DCSub */
		regw(bclamp->dc_sub & CCDC_BLK_DC_SUB_MASK, DCSUB);
		regw(0x0000, CLAMP);
		return;
	}
	/* Enable the Black clamping, set sample lines and pixels */
	val = (bclamp->start_pixel & CCDC_BLK_ST_PXL_MASK) |
	      ((bclamp->sample_pixel & CCDC_BLK_SAMPLE_LN_MASK) <<
		CCDC_BLK_SAMPLE_LN_SHIFT) | CCDC_BLK_CLAMP_ENABLE;
	regw(val, CLAMP);

	/* If Black clamping is enable then make dcsub 0 */
	val = (bclamp->sample_ln & CCDC_NUM_LINE_CALC_MASK)
			<< CCDC_NUM_LINE_CALC_SHIFT;
	regw(val, DCSUB);
}