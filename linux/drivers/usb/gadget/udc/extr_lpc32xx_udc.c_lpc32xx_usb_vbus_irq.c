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
struct lpc32xx_udc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  vbus_work (struct lpc32xx_udc*) ; 

__attribute__((used)) static irqreturn_t lpc32xx_usb_vbus_irq(int irq, void *_udc)
{
	struct lpc32xx_udc *udc = _udc;

	vbus_work(udc);

	return IRQ_HANDLED;
}