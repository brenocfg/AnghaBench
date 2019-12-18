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
typedef  unsigned int u32 ;
struct u300_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_OPEN_SOURCE 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 unsigned int U300_GPIO_PXPCR_PIN_MODE_MASK ; 
 unsigned int U300_GPIO_PXPCR_PIN_MODE_OUTPUT_OPEN_DRAIN ; 
 unsigned int U300_GPIO_PXPCR_PIN_MODE_OUTPUT_OPEN_SOURCE ; 
 unsigned int U300_GPIO_PXPCR_PIN_MODE_OUTPUT_PUSH_PULL ; 
 unsigned int U300_PIN_BIT (unsigned int) ; 
 int /*<<< orphan*/  U300_PIN_REG (unsigned int,int /*<<< orphan*/ ) ; 
 struct u300_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pcr ; 
 int /*<<< orphan*/  per ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 

int u300_gpio_config_get(struct gpio_chip *chip,
			 unsigned offset,
			 unsigned long *config)
{
	struct u300_gpio *gpio = gpiochip_get_data(chip);
	enum pin_config_param param = (enum pin_config_param) *config;
	bool biasmode;
	u32 drmode;

	/* One bit per pin, clamp to bool range */
	biasmode = !!(readl(U300_PIN_REG(offset, per)) & U300_PIN_BIT(offset));

	/* Mask out the two bits for this pin and shift to bits 0,1 */
	drmode = readl(U300_PIN_REG(offset, pcr));
	drmode &= (U300_GPIO_PXPCR_PIN_MODE_MASK << ((offset & 0x07) << 1));
	drmode >>= ((offset & 0x07) << 1);

	switch (param) {
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*config = 0;
		if (biasmode)
			return 0;
		else
			return -EINVAL;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		*config = 0;
		if (!biasmode)
			return 0;
		else
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		*config = 0;
		if (drmode == U300_GPIO_PXPCR_PIN_MODE_OUTPUT_PUSH_PULL)
			return 0;
		else
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		*config = 0;
		if (drmode == U300_GPIO_PXPCR_PIN_MODE_OUTPUT_OPEN_DRAIN)
			return 0;
		else
			return -EINVAL;
		break;
	case PIN_CONFIG_DRIVE_OPEN_SOURCE:
		*config = 0;
		if (drmode == U300_GPIO_PXPCR_PIN_MODE_OUTPUT_OPEN_SOURCE)
			return 0;
		else
			return -EINVAL;
		break;
	default:
		break;
	}
	return -ENOTSUPP;
}