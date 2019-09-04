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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN ; 
 int DC_STATE_EN_UPTO_DC6 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTIL_PIN_CTL ; 
 int UTIL_PIN_ENABLE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  assert_csr_loaded (struct drm_i915_private*) ; 

__attribute__((used)) static void assert_can_enable_dc6(struct drm_i915_private *dev_priv)
{
	WARN_ONCE(I915_READ(UTIL_PIN_CTL) & UTIL_PIN_ENABLE,
		  "Backlight is not disabled.\n");
	WARN_ONCE((I915_READ(DC_STATE_EN) & DC_STATE_EN_UPTO_DC6),
		  "DC6 already programmed to be enabled.\n");

	assert_csr_loaded(dev_priv);
}