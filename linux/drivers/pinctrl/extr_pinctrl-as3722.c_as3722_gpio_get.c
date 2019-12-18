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
struct as3722_pctrl_info {int /*<<< orphan*/  dev; struct as3722* as3722; } ;
struct as3722 {int dummy; } ;

/* Variables and functions */
 int AS3722_GPIO_INV ; 
#define  AS3722_GPIO_MODE_INPUT 134 
#define  AS3722_GPIO_MODE_INPUT_PULL_DOWN 133 
#define  AS3722_GPIO_MODE_INPUT_PULL_UP 132 
#define  AS3722_GPIO_MODE_IO_OPEN_DRAIN 131 
#define  AS3722_GPIO_MODE_IO_OPEN_DRAIN_PULL_UP 130 
 int AS3722_GPIO_MODE_MASK ; 
#define  AS3722_GPIO_MODE_OUTPUT_VDDH 129 
#define  AS3722_GPIO_MODE_OUTPUT_VDDL 128 
 int AS3722_GPIO_SIGNAL_IN_REG ; 
 int AS3722_GPIO_SIGNAL_OUT_REG ; 
 int AS3722_GPIOn_CONTROL_REG (unsigned int) ; 
 int AS3722_GPIOn_SIGNAL (unsigned int) ; 
 int EINVAL ; 
 int as3722_read (struct as3722*,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct as3722_pctrl_info* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int as3722_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct as3722_pctrl_info *as_pci = gpiochip_get_data(chip);
	struct as3722 *as3722 = as_pci->as3722;
	int ret;
	u32 reg;
	u32 control;
	u32 val;
	int mode;
	int invert_enable;

	ret = as3722_read(as3722, AS3722_GPIOn_CONTROL_REG(offset), &control);
	if (ret < 0) {
		dev_err(as_pci->dev,
			"GPIO_CONTROL%d_REG read failed: %d\n", offset, ret);
		return ret;
	}

	invert_enable = !!(control & AS3722_GPIO_INV);
	mode = control & AS3722_GPIO_MODE_MASK;
	switch (mode) {
	case AS3722_GPIO_MODE_INPUT:
	case AS3722_GPIO_MODE_INPUT_PULL_UP:
	case AS3722_GPIO_MODE_INPUT_PULL_DOWN:
	case AS3722_GPIO_MODE_IO_OPEN_DRAIN:
	case AS3722_GPIO_MODE_IO_OPEN_DRAIN_PULL_UP:
		reg = AS3722_GPIO_SIGNAL_IN_REG;
		break;
	case AS3722_GPIO_MODE_OUTPUT_VDDH:
	case AS3722_GPIO_MODE_OUTPUT_VDDL:
		reg = AS3722_GPIO_SIGNAL_OUT_REG;
		break;
	default:
		return -EINVAL;
	}

	ret = as3722_read(as3722, reg, &val);
	if (ret < 0) {
		dev_err(as_pci->dev,
			"GPIO_SIGNAL_IN_REG read failed: %d\n", ret);
		return ret;
	}

	val = !!(val & AS3722_GPIOn_SIGNAL(offset));
	return (invert_enable) ? !val : val;
}