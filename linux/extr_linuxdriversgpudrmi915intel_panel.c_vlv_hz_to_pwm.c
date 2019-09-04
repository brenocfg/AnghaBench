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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_1__ base; } ;
struct drm_i915_private {int rawclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBR1_VLV ; 
 int CBR_PWM_CLOCK_MUX_SELECT ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int KHz (int) ; 
 int MHz (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vlv_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	int mul, clock;

	if ((I915_READ(CBR1_VLV) & CBR_PWM_CLOCK_MUX_SELECT) == 0) {
		if (IS_CHERRYVIEW(dev_priv))
			clock = KHz(19200);
		else
			clock = MHz(25);
		mul = 16;
	} else {
		clock = KHz(dev_priv->rawclk_freq);
		mul = 128;
	}

	return DIV_ROUND_CLOSEST(clock, pwm_freq_hz * mul);
}