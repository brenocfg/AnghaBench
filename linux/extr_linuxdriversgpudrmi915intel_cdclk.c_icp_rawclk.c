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
 int CNP_RAWCLK_DIV (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int ICP_RAWCLK_DEN (int) ; 
 int ICP_RAWCLK_NUM (int) ; 
 int /*<<< orphan*/  PCH_RAWCLK_FREQ ; 
 int /*<<< orphan*/  SFUSE_STRAP ; 
 int SFUSE_STRAP_RAW_FREQUENCY ; 

__attribute__((used)) static int icp_rawclk(struct drm_i915_private *dev_priv)
{
	u32 rawclk;
	int divider, numerator, denominator, frequency;

	if (I915_READ(SFUSE_STRAP) & SFUSE_STRAP_RAW_FREQUENCY) {
		frequency = 24000;
		divider = 23;
		numerator = 0;
		denominator = 0;
	} else {
		frequency = 19200;
		divider = 18;
		numerator = 1;
		denominator = 4;
	}

	rawclk = CNP_RAWCLK_DIV(divider) | ICP_RAWCLK_NUM(numerator) |
		 ICP_RAWCLK_DEN(denominator);

	I915_WRITE(PCH_RAWCLK_FREQ, rawclk);
	return frequency;
}