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
typedef  size_t u32 ;
struct stm32_gpio_bank {int dummy; } ;
struct seq_file {int dummy; } ;
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct stm32_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin_nolock (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int stm32_gpio_pin (unsigned int) ; 
 int stm32_pconf_get (struct stm32_gpio_bank*,int,int) ; 
 size_t stm32_pconf_get_bias (struct stm32_gpio_bank*,int) ; 
 size_t stm32_pconf_get_driving (struct stm32_gpio_bank*,int) ; 
 size_t stm32_pconf_get_speed (struct stm32_gpio_bank*,int) ; 
 int /*<<< orphan*/  stm32_pmx_get_mode (struct stm32_gpio_bank*,int,size_t*,size_t*) ; 

__attribute__((used)) static void stm32_pconf_dbg_show(struct pinctrl_dev *pctldev,
				 struct seq_file *s,
				 unsigned int pin)
{
	struct pinctrl_gpio_range *range;
	struct stm32_gpio_bank *bank;
	int offset;
	u32 mode, alt, drive, speed, bias;
	static const char * const modes[] = {
			"input", "output", "alternate", "analog" };
	static const char * const speeds[] = {
			"low", "medium", "high", "very high" };
	static const char * const biasing[] = {
			"floating", "pull up", "pull down", "" };
	bool val;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	if (!range)
		return;

	bank = gpiochip_get_data(range->gc);
	offset = stm32_gpio_pin(pin);

	stm32_pmx_get_mode(bank, offset, &mode, &alt);
	bias = stm32_pconf_get_bias(bank, offset);

	seq_printf(s, "%s ", modes[mode]);

	switch (mode) {
	/* input */
	case 0:
		val = stm32_pconf_get(bank, offset, true);
		seq_printf(s, "- %s - %s",
			   val ? "high" : "low",
			   biasing[bias]);
		break;

	/* output */
	case 1:
		drive = stm32_pconf_get_driving(bank, offset);
		speed = stm32_pconf_get_speed(bank, offset);
		val = stm32_pconf_get(bank, offset, false);
		seq_printf(s, "- %s - %s - %s - %s %s",
			   val ? "high" : "low",
			   drive ? "open drain" : "push pull",
			   biasing[bias],
			   speeds[speed], "speed");
		break;

	/* alternate */
	case 2:
		drive = stm32_pconf_get_driving(bank, offset);
		speed = stm32_pconf_get_speed(bank, offset);
		seq_printf(s, "%d - %s - %s - %s %s", alt,
			   drive ? "open drain" : "push pull",
			   biasing[bias],
			   speeds[speed], "speed");
		break;

	/* analog */
	case 3:
		break;
	}
}