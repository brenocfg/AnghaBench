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
struct arizona_extcon_info {int micd_num_modes; int micd_mode; TYPE_1__* micd_modes; int /*<<< orphan*/  micd_pol_gpio; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int bias; int src; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_ACCDET_SRC ; 
 int /*<<< orphan*/  ARIZONA_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  ARIZONA_MICD_BIAS_SRC_MASK ; 
 int ARIZONA_MICD_BIAS_SRC_SHIFT ; 
 int /*<<< orphan*/  ARIZONA_MIC_DETECT_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arizona_extcon_set_mode(struct arizona_extcon_info *info, int mode)
{
	struct arizona *arizona = info->arizona;

	mode %= info->micd_num_modes;

	gpiod_set_value_cansleep(info->micd_pol_gpio,
				 info->micd_modes[mode].gpio);

	regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
			   ARIZONA_MICD_BIAS_SRC_MASK,
			   info->micd_modes[mode].bias <<
			   ARIZONA_MICD_BIAS_SRC_SHIFT);
	regmap_update_bits(arizona->regmap, ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_SRC, info->micd_modes[mode].src);

	info->micd_mode = mode;

	dev_dbg(arizona->dev, "Set jack polarity to %d\n", mode);
}