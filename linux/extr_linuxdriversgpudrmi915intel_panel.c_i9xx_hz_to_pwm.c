#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdclk; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;
struct drm_i915_private {TYPE_3__ cdclk; int /*<<< orphan*/  rawclk_freq; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int KHz (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i9xx_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	int clock;

	if (IS_PINEVIEW(dev_priv))
		clock = KHz(dev_priv->rawclk_freq);
	else
		clock = KHz(dev_priv->cdclk.hw.cdclk);

	return DIV_ROUND_CLOSEST(clock, pwm_freq_hz * 32);
}