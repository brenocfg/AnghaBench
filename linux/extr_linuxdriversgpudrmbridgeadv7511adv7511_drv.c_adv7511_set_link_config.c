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
struct adv7511_link_config {int clock_delay; int input_color_depth; scalar_t__ input_colorspace; scalar_t__ input_clock; size_t input_style; int input_justification; int sync_pulse; int /*<<< orphan*/  vsync_polarity; int /*<<< orphan*/  hsync_polarity; scalar_t__ embedded_sync; } ;
struct adv7511 {int rgb; int /*<<< orphan*/  vsync_polarity; int /*<<< orphan*/  hsync_polarity; scalar_t__ embedded_sync; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADV7511_INPUT_CLOCK_2X ; 
 scalar_t__ ADV7511_INPUT_CLOCK_DDR ; 
 int /*<<< orphan*/  ADV7511_REG_I2C_FREQ_ID_CFG ; 
 int ADV7511_REG_TIMING_GEN_SEQ ; 
 int /*<<< orphan*/  ADV7511_REG_VIDEO_INPUT_CFG1 ; 
 int ADV7511_REG_VIDEO_INPUT_CFG2 ; 
 scalar_t__ HDMI_COLORSPACE_RGB ; 
 scalar_t__ HDMI_COLORSPACE_YUV422 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void adv7511_set_link_config(struct adv7511 *adv7511,
				    const struct adv7511_link_config *config)
{
	/*
	 * The input style values documented in the datasheet don't match the
	 * hardware register field values :-(
	 */
	static const unsigned int input_styles[4] = { 0, 2, 1, 3 };

	unsigned int clock_delay;
	unsigned int color_depth;
	unsigned int input_id;

	clock_delay = (config->clock_delay + 1200) / 400;
	color_depth = config->input_color_depth == 8 ? 3
		    : (config->input_color_depth == 10 ? 1 : 2);

	/* TODO Support input ID 6 */
	if (config->input_colorspace != HDMI_COLORSPACE_YUV422)
		input_id = config->input_clock == ADV7511_INPUT_CLOCK_DDR
			 ? 5 : 0;
	else if (config->input_clock == ADV7511_INPUT_CLOCK_DDR)
		input_id = config->embedded_sync ? 8 : 7;
	else if (config->input_clock == ADV7511_INPUT_CLOCK_2X)
		input_id = config->embedded_sync ? 4 : 3;
	else
		input_id = config->embedded_sync ? 2 : 1;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2C_FREQ_ID_CFG, 0xf,
			   input_id);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_VIDEO_INPUT_CFG1, 0x7e,
			   (color_depth << 4) |
			   (input_styles[config->input_style] << 2));
	regmap_write(adv7511->regmap, ADV7511_REG_VIDEO_INPUT_CFG2,
		     config->input_justification << 3);
	regmap_write(adv7511->regmap, ADV7511_REG_TIMING_GEN_SEQ,
		     config->sync_pulse << 2);

	regmap_write(adv7511->regmap, 0xba, clock_delay << 5);

	adv7511->embedded_sync = config->embedded_sync;
	adv7511->hsync_polarity = config->hsync_polarity;
	adv7511->vsync_polarity = config->vsync_polarity;
	adv7511->rgb = config->input_colorspace == HDMI_COLORSPACE_RGB;
}