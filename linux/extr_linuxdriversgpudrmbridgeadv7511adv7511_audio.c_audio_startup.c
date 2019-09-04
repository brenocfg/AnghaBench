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
struct device {int dummy; } ;
struct adv7511 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_REG_AUDIO_CFG1 ; 
 int /*<<< orphan*/  ADV7511_REG_AUDIO_CONFIG ; 
 int /*<<< orphan*/  ADV7511_REG_GC (int) ; 
 int /*<<< orphan*/  ADV7511_REG_INFOFRAME_UPDATE ; 
 int /*<<< orphan*/  ADV7511_REG_PACKET_ENABLE1 ; 
 int BIT (int) ; 
 struct adv7511* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int audio_startup(struct device *dev, void *data)
{
	struct adv7511 *adv7511 = dev_get_drvdata(dev);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG,
				BIT(7), 0);

	/* hide Audio infoframe updates */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_INFOFRAME_UPDATE,
				BIT(5), BIT(5));
	/* enable N/CTS, enable Audio sample packets */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(5), BIT(5));
	/* enable N/CTS */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(6), BIT(6));
	/* not copyrighted */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CFG1,
				BIT(5), BIT(5));
	/* enable audio infoframes */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(3), BIT(3));
	/* AV mute disable */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_GC(0),
				BIT(7) | BIT(6), BIT(7));
	/* use Audio infoframe updated info */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_GC(1),
				BIT(5), 0);
	return 0;
}