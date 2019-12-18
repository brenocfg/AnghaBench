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
struct drm_i915_private {int fsb_freq; int mem_freq; int is_ddr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKCFG ; 
#define  CLKCFG_FSB_400 134 
#define  CLKCFG_FSB_533 133 
#define  CLKCFG_FSB_667 132 
#define  CLKCFG_FSB_800 131 
 int CLKCFG_FSB_MASK ; 
#define  CLKCFG_MEM_533 130 
#define  CLKCFG_MEM_667 129 
#define  CLKCFG_MEM_800 128 
 int CLKCFG_MEM_MASK ; 
 int /*<<< orphan*/  CSHRDDR3CTL ; 
 int CSHRDDR3CTL_DDR3 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_pineview_get_mem_freq(struct drm_i915_private *dev_priv)
{
	u32 tmp;

	tmp = I915_READ(CLKCFG);

	switch (tmp & CLKCFG_FSB_MASK) {
	case CLKCFG_FSB_533:
		dev_priv->fsb_freq = 533; /* 133*4 */
		break;
	case CLKCFG_FSB_800:
		dev_priv->fsb_freq = 800; /* 200*4 */
		break;
	case CLKCFG_FSB_667:
		dev_priv->fsb_freq =  667; /* 167*4 */
		break;
	case CLKCFG_FSB_400:
		dev_priv->fsb_freq = 400; /* 100*4 */
		break;
	}

	switch (tmp & CLKCFG_MEM_MASK) {
	case CLKCFG_MEM_533:
		dev_priv->mem_freq = 533;
		break;
	case CLKCFG_MEM_667:
		dev_priv->mem_freq = 667;
		break;
	case CLKCFG_MEM_800:
		dev_priv->mem_freq = 800;
		break;
	}

	/* detect pineview DDR3 setting */
	tmp = I915_READ(CSHRDDR3CTL);
	dev_priv->is_ddr3 = (tmp & CSHRDDR3CTL_DDR3) ? 1 : 0;
}