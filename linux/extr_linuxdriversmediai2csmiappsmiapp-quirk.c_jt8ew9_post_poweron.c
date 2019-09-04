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
struct smiapp_sensor {int dummy; } ;
struct smiapp_reg_8 {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct smiapp_reg_8 const*) ; 
 int smiapp_write_8s (struct smiapp_sensor*,struct smiapp_reg_8 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jt8ew9_post_poweron(struct smiapp_sensor *sensor)
{
	static const struct smiapp_reg_8 regs[] = {
		{ 0x30a3, 0xd8 }, /* Output port control : LVDS ports only */
		{ 0x30ae, 0x00 }, /* 0x0307 pll_multiplier maximum value on PLL input 9.6MHz ( 19.2MHz is divided on pre_pll_div) */
		{ 0x30af, 0xd0 }, /* 0x0307 pll_multiplier maximum value on PLL input 9.6MHz ( 19.2MHz is divided on pre_pll_div) */
		{ 0x322d, 0x04 }, /* Adjusting Processing Image Size to Scaler Toshiba Recommendation Setting */
		{ 0x3255, 0x0f }, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		{ 0x3256, 0x15 }, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		{ 0x3258, 0x70 }, /* Analog Gain Control Toshiba Recommendation Setting */
		{ 0x3259, 0x70 }, /* Analog Gain Control Toshiba Recommendation Setting */
		{ 0x325f, 0x7c }, /* Analog Gain Control Toshiba Recommendation Setting */
		{ 0x3302, 0x06 }, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		{ 0x3304, 0x00 }, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		{ 0x3307, 0x22 }, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		{ 0x3308, 0x8d }, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		{ 0x331e, 0x0f }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x3320, 0x30 }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x3321, 0x11 }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x3322, 0x98 }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x3323, 0x64 }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x3325, 0x83 }, /* Read Out Timing Control Toshiba Recommendation Setting */
		{ 0x3330, 0x18 }, /* Read Out Timing Control Toshiba Recommendation Setting */
		{ 0x333c, 0x01 }, /* Read Out Timing Control Toshiba Recommendation Setting */
		{ 0x3345, 0x2f }, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		{ 0x33de, 0x38 }, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		/* Taken from v03. No idea what the rest are. */
		{ 0x32e0, 0x05 },
		{ 0x32e1, 0x05 },
		{ 0x32e2, 0x04 },
		{ 0x32e5, 0x04 },
		{ 0x32e6, 0x04 },

	};

	return smiapp_write_8s(sensor, regs, ARRAY_SIZE(regs));
}