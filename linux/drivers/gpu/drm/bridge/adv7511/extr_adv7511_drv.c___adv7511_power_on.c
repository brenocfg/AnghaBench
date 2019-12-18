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
struct adv7511 {int current_edid_segment; int /*<<< orphan*/  regmap; TYPE_1__* i2c_main; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int ADV7511_INT0_EDID_READY ; 
 int ADV7511_INT0_HPD ; 
 int /*<<< orphan*/  ADV7511_INT1_DDC_ERROR ; 
 int /*<<< orphan*/  ADV7511_POWER_POWER_DOWN ; 
 int /*<<< orphan*/  ADV7511_REG_INT_ENABLE (int) ; 
 int /*<<< orphan*/  ADV7511_REG_POWER ; 
 int /*<<< orphan*/  ADV7511_REG_POWER2 ; 
 int /*<<< orphan*/  ADV7511_REG_POWER2_HPD_SRC_MASK ; 
 int /*<<< orphan*/  ADV7511_REG_POWER2_HPD_SRC_NONE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __adv7511_power_on(struct adv7511 *adv7511)
{
	adv7511->current_edid_segment = -1;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER,
			   ADV7511_POWER_POWER_DOWN, 0);
	if (adv7511->i2c_main->irq) {
		/*
		 * Documentation says the INT_ENABLE registers are reset in
		 * POWER_DOWN mode. My 7511w preserved the bits, however.
		 * Still, let's be safe and stick to the documentation.
		 */
		regmap_write(adv7511->regmap, ADV7511_REG_INT_ENABLE(0),
			     ADV7511_INT0_EDID_READY | ADV7511_INT0_HPD);
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1),
				   ADV7511_INT1_DDC_ERROR,
				   ADV7511_INT1_DDC_ERROR);
	}

	/*
	 * Per spec it is allowed to pulse the HPD signal to indicate that the
	 * EDID information has changed. Some monitors do this when they wakeup
	 * from standby or are enabled. When the HPD goes low the adv7511 is
	 * reset and the outputs are disabled which might cause the monitor to
	 * go to standby again. To avoid this we ignore the HPD pin for the
	 * first few seconds after enabling the output.
	 */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER2,
			   ADV7511_REG_POWER2_HPD_SRC_MASK,
			   ADV7511_REG_POWER2_HPD_SRC_NONE);
}