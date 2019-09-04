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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdvo_device_mapping {size_t i2c_pin; size_t i2c_speed; scalar_t__ initialized; } ;
struct psb_intel_sdvo {int /*<<< orphan*/ * i2c; } ;
struct drm_psb_private {TYPE_1__* gmbus; struct sdvo_device_mapping* sdvo_mappings; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 size_t GMBUS_NUM_PORTS ; 
 size_t GMBUS_PORT_DPB ; 
 int GMBUS_RATE_1MHZ ; 
 scalar_t__ IS_SDVOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_intel_gmbus_force_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gma_intel_gmbus_set_speed (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
psb_intel_sdvo_select_i2c_bus(struct drm_psb_private *dev_priv,
			  struct psb_intel_sdvo *sdvo, u32 reg)
{
	struct sdvo_device_mapping *mapping;
	u8 pin, speed;

	if (IS_SDVOB(reg))
		mapping = &dev_priv->sdvo_mappings[0];
	else
		mapping = &dev_priv->sdvo_mappings[1];

	pin = GMBUS_PORT_DPB;
	speed = GMBUS_RATE_1MHZ >> 8;
	if (mapping->initialized) {
		pin = mapping->i2c_pin;
		speed = mapping->i2c_speed;
	}

	if (pin < GMBUS_NUM_PORTS) {
		sdvo->i2c = &dev_priv->gmbus[pin].adapter;
		gma_intel_gmbus_set_speed(sdvo->i2c, speed);
		gma_intel_gmbus_force_bit(sdvo->i2c, true);
	} else
		sdvo->i2c = &dev_priv->gmbus[GMBUS_PORT_DPB].adapter;
}