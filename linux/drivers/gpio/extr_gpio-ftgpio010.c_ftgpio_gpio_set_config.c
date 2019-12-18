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
typedef  int u32 ;
struct gpio_chip {int dummy; } ;
struct ftgpio_gpio {scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int ENOTSUPP ; 
 scalar_t__ GPIO_DEBOUNCE_EN ; 
 scalar_t__ GPIO_DEBOUNCE_PRESCALE ; 
 int PIN_CONFIG_INPUT_DEBOUNCE ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned long) ; 
 struct ftgpio_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ftgpio_gpio_set_config(struct gpio_chip *gc, unsigned int offset,
				  unsigned long config)
{
	enum pin_config_param param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);
	struct ftgpio_gpio *g = gpiochip_get_data(gc);
	unsigned long pclk_freq;
	u32 deb_div;
	u32 val;

	if (param != PIN_CONFIG_INPUT_DEBOUNCE)
		return -ENOTSUPP;

	/*
	 * Debounce only works if interrupts are enabled. The manual
	 * states that if PCLK is 66 MHz, and this is set to 0x7D0, then
	 * PCLK is divided down to 33 kHz for the debounce timer. 0x7D0 is
	 * 2000 decimal, so what they mean is simply that the PCLK is
	 * divided by this value.
	 *
	 * As we get a debounce setting in microseconds, we calculate the
	 * desired period time and see if we can get a suitable debounce
	 * time.
	 */
	pclk_freq = clk_get_rate(g->clk);
	deb_div = DIV_ROUND_CLOSEST(pclk_freq, arg);

	/* This register is only 24 bits wide */
	if (deb_div > (1 << 24))
		return -ENOTSUPP;

	dev_dbg(g->dev, "prescale divisor: %08x, resulting frequency %lu Hz\n",
		deb_div, (pclk_freq/deb_div));

	val = readl(g->base + GPIO_DEBOUNCE_PRESCALE);
	if (val == deb_div) {
		/*
		 * The debounce timer happens to already be set to the
		 * desireable value, what a coincidence! We can just enable
		 * debounce on this GPIO line and return. This happens more
		 * often than you think, for example when all GPIO keys
		 * on a system are requesting the same debounce interval.
		 */
		val = readl(g->base + GPIO_DEBOUNCE_EN);
		val |= BIT(offset);
		writel(val, g->base + GPIO_DEBOUNCE_EN);
		return 0;
	}

	val = readl(g->base + GPIO_DEBOUNCE_EN);
	if (val) {
		/*
		 * Oh no! Someone is already using the debounce with
		 * another setting than what we need. Bummer.
		 */
		return -ENOTSUPP;
	}

	/* First come, first serve */
	writel(deb_div, g->base + GPIO_DEBOUNCE_PRESCALE);
	/* Enable debounce */
	val |= BIT(offset);
	writel(val, g->base + GPIO_DEBOUNCE_EN);

	return 0;
}