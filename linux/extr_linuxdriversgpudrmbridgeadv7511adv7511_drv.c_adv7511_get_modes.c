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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct adv7511 {int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  rgb; int /*<<< orphan*/  powered; int /*<<< orphan*/  regmap; TYPE_1__* i2c_edid; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_REG_EDID_I2C_ADDR ; 
 int /*<<< orphan*/  __adv7511_power_off (struct adv7511*) ; 
 int /*<<< orphan*/  __adv7511_power_on (struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_get_edid_block ; 
 int /*<<< orphan*/  adv7511_set_config_csc (struct adv7511*,struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_s_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 unsigned int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (struct edid*) ; 
 struct edid* drm_do_get_edid (struct drm_connector*,int /*<<< orphan*/ ,struct adv7511*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int adv7511_get_modes(struct adv7511 *adv7511,
			     struct drm_connector *connector)
{
	struct edid *edid;
	unsigned int count;

	/* Reading the EDID only works if the device is powered */
	if (!adv7511->powered) {
		unsigned int edid_i2c_addr =
					(adv7511->i2c_edid->addr << 1);

		__adv7511_power_on(adv7511);

		/* Reset the EDID_I2C_ADDR register as it might be cleared */
		regmap_write(adv7511->regmap, ADV7511_REG_EDID_I2C_ADDR,
			     edid_i2c_addr);
	}

	edid = drm_do_get_edid(connector, adv7511_get_edid_block, adv7511);

	if (!adv7511->powered)
		__adv7511_power_off(adv7511);


	drm_connector_update_edid_property(connector, edid);
	count = drm_add_edid_modes(connector, edid);

	adv7511_set_config_csc(adv7511, connector, adv7511->rgb,
			       drm_detect_hdmi_monitor(edid));

	cec_s_phys_addr_from_edid(adv7511->cec_adap, edid);

	kfree(edid);

	return count;
}