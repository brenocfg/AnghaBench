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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNP_RAWCLK_DIV (int) ; 
 int /*<<< orphan*/  CNP_RAWCLK_FRAC (scalar_t__) ; 
 scalar_t__ DIV_ROUND_CLOSEST (int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_RAWCLK_FREQ ; 
 int /*<<< orphan*/  SFUSE_STRAP ; 
 int SFUSE_STRAP_RAW_FREQUENCY ; 

__attribute__((used)) static int cnp_rawclk(struct drm_i915_private *dev_priv)
{
	u32 rawclk;
	int divider, fraction;

	if (I915_READ(SFUSE_STRAP) & SFUSE_STRAP_RAW_FREQUENCY) {
		/* 24 MHz */
		divider = 24000;
		fraction = 0;
	} else {
		/* 19.2 MHz */
		divider = 19000;
		fraction = 200;
	}

	rawclk = CNP_RAWCLK_DIV((divider / 1000) - 1);
	if (fraction)
		rawclk |= CNP_RAWCLK_FRAC(DIV_ROUND_CLOSEST(1000,
							    fraction) - 1);

	I915_WRITE(PCH_RAWCLK_FREQ, rawclk);
	return divider + fraction;
}