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
struct lpc32xx_udc {int pullup; int /*<<< orphan*/  pullup_job; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp1301_pullup_set (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp1301_pullup_enable(struct lpc32xx_udc *udc, int en_pullup,
				  int block)
{
	if (en_pullup == udc->pullup)
		return;

	udc->pullup = en_pullup;
	if (block)
		isp1301_pullup_set(udc);
	else
		/* defer slow i2c pull up setting */
		schedule_work(&udc->pullup_job);
}