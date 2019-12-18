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
struct mipi_dsi_device {int lanes; } ;
struct adv7511 {int /*<<< orphan*/  regmap_cec; scalar_t__ use_timing_gen; struct mipi_dsi_device* dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7511_dsi_config_timing_gen (struct adv7511*) ; 
 int /*<<< orphan*/  adv7533_cec_fixed_registers ; 
 int /*<<< orphan*/  regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 

void adv7533_dsi_power_on(struct adv7511 *adv)
{
	struct mipi_dsi_device *dsi = adv->dsi;

	if (adv->use_timing_gen)
		adv7511_dsi_config_timing_gen(adv);

	/* set number of dsi lanes */
	regmap_write(adv->regmap_cec, 0x1c, dsi->lanes << 4);

	if (adv->use_timing_gen) {
		/* reset internal timing generator */
		regmap_write(adv->regmap_cec, 0x27, 0xcb);
		regmap_write(adv->regmap_cec, 0x27, 0x8b);
		regmap_write(adv->regmap_cec, 0x27, 0xcb);
	} else {
		/* disable internal timing generator */
		regmap_write(adv->regmap_cec, 0x27, 0x0b);
	}

	/* enable hdmi */
	regmap_write(adv->regmap_cec, 0x03, 0x89);
	/* disable test mode */
	regmap_write(adv->regmap_cec, 0x55, 0x00);

	regmap_register_patch(adv->regmap_cec, adv7533_cec_fixed_registers,
			      ARRAY_SIZE(adv7533_cec_fixed_registers));
}