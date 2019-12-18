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
struct bcm2835_pinctrl {int /*<<< orphan*/  dev; } ;
typedef  enum bcm2835_fsel { ____Placeholder_bcm2835_fsel } bcm2835_fsel ;

/* Variables and functions */
 int BCM2835_FSEL_GPIO_IN ; 
 int BCM2835_FSEL_MASK ; 
 int /*<<< orphan*/  FSEL_REG (unsigned int) ; 
 int FSEL_SHIFT (unsigned int) ; 
 int /*<<< orphan*/ * bcm2835_functions ; 
 int bcm2835_gpio_rd (struct bcm2835_pinctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_gpio_wr (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm2835_pinctrl_fsel_set(
		struct bcm2835_pinctrl *pc, unsigned pin,
		enum bcm2835_fsel fsel)
{
	u32 val = bcm2835_gpio_rd(pc, FSEL_REG(pin));
	enum bcm2835_fsel cur = (val >> FSEL_SHIFT(pin)) & BCM2835_FSEL_MASK;

	dev_dbg(pc->dev, "read %08x (%u => %s)\n", val, pin,
			bcm2835_functions[cur]);

	if (cur == fsel)
		return;

	if (cur != BCM2835_FSEL_GPIO_IN && fsel != BCM2835_FSEL_GPIO_IN) {
		/* always transition through GPIO_IN */
		val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
		val |= BCM2835_FSEL_GPIO_IN << FSEL_SHIFT(pin);

		dev_dbg(pc->dev, "trans %08x (%u <= %s)\n", val, pin,
				bcm2835_functions[BCM2835_FSEL_GPIO_IN]);
		bcm2835_gpio_wr(pc, FSEL_REG(pin), val);
	}

	val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
	val |= fsel << FSEL_SHIFT(pin);

	dev_dbg(pc->dev, "write %08x (%u <= %s)\n", val, pin,
			bcm2835_functions[fsel]);
	bcm2835_gpio_wr(pc, FSEL_REG(pin), val);
}