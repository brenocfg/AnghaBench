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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct gpio_map {int init; int /*<<< orphan*/  base_offset; } ;
struct TYPE_3__ {int seq_version; } ;
struct TYPE_4__ {TYPE_1__ dsi; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct gpio_map*) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 size_t IOSF_PORT_GPIO_NC ; 
 int /*<<< orphan*/  VLV_GPIO_PAD_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_GPIO_PCONF0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_IOSF_SB_GPIO ; 
 struct gpio_map* vlv_gpio_table ; 
 int /*<<< orphan*/  vlv_iosf_sb_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_iosf_sb_write (struct drm_i915_private*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlv_exec_gpio(struct drm_i915_private *dev_priv,
			  u8 gpio_source, u8 gpio_index, bool value)
{
	struct gpio_map *map;
	u16 pconf0, padval;
	u32 tmp;
	u8 port;

	if (gpio_index >= ARRAY_SIZE(vlv_gpio_table)) {
		DRM_DEBUG_KMS("unknown gpio index %u\n", gpio_index);
		return;
	}

	map = &vlv_gpio_table[gpio_index];

	if (dev_priv->vbt.dsi.seq_version >= 3) {
		/* XXX: this assumes vlv_gpio_table only has NC GPIOs. */
		port = IOSF_PORT_GPIO_NC;
	} else {
		if (gpio_source == 0) {
			port = IOSF_PORT_GPIO_NC;
		} else if (gpio_source == 1) {
			DRM_DEBUG_KMS("SC gpio not supported\n");
			return;
		} else {
			DRM_DEBUG_KMS("unknown gpio source %u\n", gpio_source);
			return;
		}
	}

	pconf0 = VLV_GPIO_PCONF0(map->base_offset);
	padval = VLV_GPIO_PAD_VAL(map->base_offset);

	vlv_iosf_sb_get(dev_priv, BIT(VLV_IOSF_SB_GPIO));
	if (!map->init) {
		/* FIXME: remove constant below */
		vlv_iosf_sb_write(dev_priv, port, pconf0, 0x2000CC00);
		map->init = true;
	}

	tmp = 0x4 | value;
	vlv_iosf_sb_write(dev_priv, port, padval, tmp);
	vlv_iosf_sb_put(dev_priv, BIT(VLV_IOSF_SB_GPIO));
}