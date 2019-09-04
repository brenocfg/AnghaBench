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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int ngpio; } ;
struct pca953x_chip {int /*<<< orphan*/  client; TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int BANK_SZ ; 
 int /*<<< orphan*/  NBANK (struct pca953x_chip*) ; 
 int PCAL_GPIO_MASK ; 
 int PCAL_PINCTRL_MASK ; 
 int REG_ADDR_AI ; 
 int fls (int) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca953x_read_regs_24(struct pca953x_chip *chip, int reg, u8 *val)
{
	int bank_shift = fls((chip->gpio_chip.ngpio - 1) / BANK_SZ);
	int addr = (reg & PCAL_GPIO_MASK) << bank_shift;
	int pinctrl = (reg & PCAL_PINCTRL_MASK) << 1;

	return i2c_smbus_read_i2c_block_data(chip->client,
					     pinctrl | addr | REG_ADDR_AI,
					     NBANK(chip), val);
}