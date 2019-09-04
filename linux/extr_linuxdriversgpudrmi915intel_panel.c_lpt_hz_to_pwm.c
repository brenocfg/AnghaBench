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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ alternate_pwm_increment; } ;
struct intel_panel {TYPE_2__ backlight; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 scalar_t__ HAS_PCH_LPT_H (struct drm_i915_private*) ; 
 int MHz (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 lpt_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;
	u32 mul, clock;

	if (panel->backlight.alternate_pwm_increment)
		mul = 16;
	else
		mul = 128;

	if (HAS_PCH_LPT_H(dev_priv))
		clock = MHz(135); /* LPT:H */
	else
		clock = MHz(24); /* LPT:LP */

	return DIV_ROUND_CLOSEST(clock, pwm_freq_hz * mul);
}