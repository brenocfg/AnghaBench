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
typedef  int u8 ;
struct lp3943_reg_cfg {int mask; int shift; int /*<<< orphan*/  reg; } ;
struct lp3943_gpio {struct lp3943* lp3943; } ;
struct lp3943 {struct lp3943_reg_cfg* mux_cfg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int LP3943_GPIO_OUT_HIGH ; 
 int LP3943_GPIO_OUT_LOW ; 
 int lp3943_read_byte (struct lp3943*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp3943_get_gpio_out_status(struct lp3943_gpio *lp3943_gpio,
				      struct gpio_chip *chip, unsigned offset)
{
	struct lp3943 *lp3943 = lp3943_gpio->lp3943;
	const struct lp3943_reg_cfg *mux = lp3943->mux_cfg;
	u8 read;
	int err;

	err = lp3943_read_byte(lp3943, mux[offset].reg, &read);
	if (err)
		return err;

	read = (read & mux[offset].mask) >> mux[offset].shift;

	if (read == LP3943_GPIO_OUT_HIGH)
		return 1;
	else if (read == LP3943_GPIO_OUT_LOW)
		return 0;
	else
		return -EINVAL;
}