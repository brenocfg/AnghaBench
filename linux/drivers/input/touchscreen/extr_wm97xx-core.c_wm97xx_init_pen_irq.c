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
typedef  int u16 ;
struct wm97xx {scalar_t__ id; TYPE_1__* mach_ops; scalar_t__ pen_irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int irq_gpio; int /*<<< orphan*/  irq_enable; } ;

/* Variables and functions */
 int AC97_MISC_AFE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ WM9705_ID2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wm97xx*) ; 
 int /*<<< orphan*/  wm97xx_pen_interrupt ; 
 int wm97xx_reg_read (struct wm97xx*,int) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int,int) ; 

__attribute__((used)) static int wm97xx_init_pen_irq(struct wm97xx *wm)
{
	u16 reg;

	/* If an interrupt is supplied an IRQ enable operation must also be
	 * provided. */
	BUG_ON(!wm->mach_ops->irq_enable);

	if (request_irq(wm->pen_irq, wm97xx_pen_interrupt, IRQF_SHARED,
			"wm97xx-pen", wm)) {
		dev_err(wm->dev,
			"Failed to register pen down interrupt, polling");
		wm->pen_irq = 0;
		return -EINVAL;
	}

	/* Configure GPIO as interrupt source on WM971x */
	if (wm->id != WM9705_ID2) {
		BUG_ON(!wm->mach_ops->irq_gpio);
		reg = wm97xx_reg_read(wm, AC97_MISC_AFE);
		wm97xx_reg_write(wm, AC97_MISC_AFE,
				reg & ~(wm->mach_ops->irq_gpio));
		reg = wm97xx_reg_read(wm, 0x5a);
		wm97xx_reg_write(wm, 0x5a, reg & ~0x0001);
	}

	return 0;
}