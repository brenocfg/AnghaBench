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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int seq_version; } ;
struct TYPE_4__ {TYPE_1__ dsi; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int CHV_GPIO_GPIOCFG_GPO ; 
 int CHV_GPIO_GPIOEN ; 
 int CHV_GPIO_GPIOTXSTATE (int) ; 
 scalar_t__ CHV_GPIO_IDX_START_E ; 
 scalar_t__ CHV_GPIO_IDX_START_SE ; 
 scalar_t__ CHV_GPIO_IDX_START_SW ; 
 scalar_t__ CHV_GPIO_PAD_CFG0 (scalar_t__,scalar_t__) ; 
 scalar_t__ CHV_GPIO_PAD_CFG1 (scalar_t__,scalar_t__) ; 
 scalar_t__ CHV_IOSF_PORT_GPIO_E ; 
 scalar_t__ CHV_IOSF_PORT_GPIO_N ; 
 scalar_t__ CHV_IOSF_PORT_GPIO_SE ; 
 scalar_t__ CHV_IOSF_PORT_GPIO_SW ; 
 scalar_t__ CHV_VBT_MAX_PINS_PER_FMLY ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  VLV_IOSF_SB_GPIO ; 
 int /*<<< orphan*/  vlv_iosf_sb_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_iosf_sb_write (struct drm_i915_private*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void chv_exec_gpio(struct drm_i915_private *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
{
	u16 cfg0, cfg1;
	u16 family_num;
	u8 port;

	if (dev_priv->vbt.dsi.seq_version >= 3) {
		if (gpio_index >= CHV_GPIO_IDX_START_SE) {
			/* XXX: it's unclear whether 255->57 is part of SE. */
			gpio_index -= CHV_GPIO_IDX_START_SE;
			port = CHV_IOSF_PORT_GPIO_SE;
		} else if (gpio_index >= CHV_GPIO_IDX_START_SW) {
			gpio_index -= CHV_GPIO_IDX_START_SW;
			port = CHV_IOSF_PORT_GPIO_SW;
		} else if (gpio_index >= CHV_GPIO_IDX_START_E) {
			gpio_index -= CHV_GPIO_IDX_START_E;
			port = CHV_IOSF_PORT_GPIO_E;
		} else {
			port = CHV_IOSF_PORT_GPIO_N;
		}
	} else {
		/* XXX: The spec is unclear about CHV GPIO on seq v2 */
		if (gpio_source != 0) {
			DRM_DEBUG_KMS("unknown gpio source %u\n", gpio_source);
			return;
		}

		if (gpio_index >= CHV_GPIO_IDX_START_E) {
			DRM_DEBUG_KMS("invalid gpio index %u for GPIO N\n",
				      gpio_index);
			return;
		}

		port = CHV_IOSF_PORT_GPIO_N;
	}

	family_num = gpio_index / CHV_VBT_MAX_PINS_PER_FMLY;
	gpio_index = gpio_index % CHV_VBT_MAX_PINS_PER_FMLY;

	cfg0 = CHV_GPIO_PAD_CFG0(family_num, gpio_index);
	cfg1 = CHV_GPIO_PAD_CFG1(family_num, gpio_index);

	vlv_iosf_sb_get(dev_priv, BIT(VLV_IOSF_SB_GPIO));
	vlv_iosf_sb_write(dev_priv, port, cfg1, 0);
	vlv_iosf_sb_write(dev_priv, port, cfg0,
			  CHV_GPIO_GPIOEN | CHV_GPIO_GPIOCFG_GPO |
			  CHV_GPIO_GPIOTXSTATE(value));
	vlv_iosf_sb_put(dev_priv, BIT(VLV_IOSF_SB_GPIO));
}