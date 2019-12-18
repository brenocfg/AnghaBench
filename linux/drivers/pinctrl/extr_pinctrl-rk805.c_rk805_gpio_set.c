#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rk805_pctrl_info {int /*<<< orphan*/  dev; TYPE_2__* pin_cfg; TYPE_1__* rk808; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  val_msk; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 struct rk805_pctrl_info* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk805_gpio_set(struct gpio_chip *chip,
			   unsigned int offset,
			   int value)
{
	struct rk805_pctrl_info *pci = gpiochip_get_data(chip);
	int ret;

	ret = regmap_update_bits(pci->rk808->regmap,
				 pci->pin_cfg[offset].reg,
				 pci->pin_cfg[offset].val_msk,
				 value ? pci->pin_cfg[offset].val_msk : 0);
	if (ret)
		dev_err(pci->dev, "set gpio%d value %d failed\n",
			offset, value);
}