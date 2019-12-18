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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKCFG ; 
#define  CLKCFG_FSB_1067 135 
#define  CLKCFG_FSB_1067_ALT 134 
#define  CLKCFG_FSB_1333 133 
#define  CLKCFG_FSB_1333_ALT 132 
#define  CLKCFG_FSB_400 131 
#define  CLKCFG_FSB_533 130 
#define  CLKCFG_FSB_667 129 
#define  CLKCFG_FSB_800 128 
 int CLKCFG_FSB_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g4x_hrawclk(struct drm_i915_private *dev_priv)
{
	u32 clkcfg;

	/* hrawclock is 1/4 the FSB frequency */
	clkcfg = I915_READ(CLKCFG);
	switch (clkcfg & CLKCFG_FSB_MASK) {
	case CLKCFG_FSB_400:
		return 100000;
	case CLKCFG_FSB_533:
		return 133333;
	case CLKCFG_FSB_667:
		return 166667;
	case CLKCFG_FSB_800:
		return 200000;
	case CLKCFG_FSB_1067:
	case CLKCFG_FSB_1067_ALT:
		return 266667;
	case CLKCFG_FSB_1333:
	case CLKCFG_FSB_1333_ALT:
		return 333333;
	default:
		return 133333;
	}
}