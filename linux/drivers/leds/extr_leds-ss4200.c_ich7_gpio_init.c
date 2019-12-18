#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_3__ {int gpio_bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ GPIO_USE_SEL ; 
 scalar_t__ GPI_INV ; 
 scalar_t__ GPO_BLINK ; 
 scalar_t__ GP_IO_SEL ; 
 scalar_t__ GP_LVL ; 
 int NAS_RECOVERY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int inl (scalar_t__) ; 
 scalar_t__ nas_gpio_io_base ; 
 int /*<<< orphan*/  nasgpio_gpio_lock ; 
 TYPE_1__* nasgpio_leds ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ich7_gpio_init(struct device *dev)
{
	int i;
	u32 config_data = 0;
	u32 all_nas_led = 0;

	for (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++)
		all_nas_led |= (1<<nasgpio_leds[i].gpio_bit);

	spin_lock(&nasgpio_gpio_lock);
	/*
	 * We need to enable all of the GPIO lines used by the NAS box,
	 * so we will read the current Use Selection and add our usage
	 * to it.  This should be benign with regard to the original
	 * BIOS configuration.
	 */
	config_data = inl(nas_gpio_io_base + GPIO_USE_SEL);
	dev_dbg(dev, ": Data read from GPIO_USE_SEL = 0x%08x\n", config_data);
	config_data |= all_nas_led + NAS_RECOVERY;
	outl(config_data, nas_gpio_io_base + GPIO_USE_SEL);
	config_data = inl(nas_gpio_io_base + GPIO_USE_SEL);
	dev_dbg(dev, ": GPIO_USE_SEL = 0x%08x\n\n", config_data);

	/*
	 * The LED GPIO outputs need to be configured for output, so we
	 * will ensure that all LED lines are cleared for output and the
	 * RECOVERY line ready for input.  This too should be benign with
	 * regard to BIOS configuration.
	 */
	config_data = inl(nas_gpio_io_base + GP_IO_SEL);
	dev_dbg(dev, ": Data read from GP_IO_SEL = 0x%08x\n",
					config_data);
	config_data &= ~all_nas_led;
	config_data |= NAS_RECOVERY;
	outl(config_data, nas_gpio_io_base + GP_IO_SEL);
	config_data = inl(nas_gpio_io_base + GP_IO_SEL);
	dev_dbg(dev, ": GP_IO_SEL = 0x%08x\n", config_data);

	/*
	 * In our final system, the BIOS will initialize the state of all
	 * of the LEDs.  For now, we turn them all off (or Low).
	 */
	config_data = inl(nas_gpio_io_base + GP_LVL);
	dev_dbg(dev, ": Data read from GP_LVL = 0x%08x\n", config_data);
	/*
	 * In our final system, the BIOS will initialize the blink state of all
	 * of the LEDs.  For now, we turn blink off for all of them.
	 */
	config_data = inl(nas_gpio_io_base + GPO_BLINK);
	dev_dbg(dev, ": Data read from GPO_BLINK = 0x%08x\n", config_data);

	/*
	 * At this moment, I am unsure if anything needs to happen with GPI_INV
	 */
	config_data = inl(nas_gpio_io_base + GPI_INV);
	dev_dbg(dev, ": Data read from GPI_INV = 0x%08x\n", config_data);

	spin_unlock(&nasgpio_gpio_lock);
	return 0;
}