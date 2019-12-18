#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ speed; } ;
struct pxa25x_udc {int active; int /*<<< orphan*/  clk; TYPE_3__* driver; TYPE_1__ gadget; int /*<<< orphan*/  suspended; scalar_t__ pullup; scalar_t__ vbus; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_6__ {TYPE_2__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*,char*) ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_activity (struct pxa25x_udc*,TYPE_3__*) ; 
 int /*<<< orphan*/  udc_disable (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  udc_enable (struct pxa25x_udc*) ; 

__attribute__((used)) static int pullup(struct pxa25x_udc *udc)
{
	int is_active = udc->vbus && udc->pullup && !udc->suspended;
	DMSG("%s\n", is_active ? "active" : "inactive");
	if (is_active) {
		if (!udc->active) {
			udc->active = 1;
			/* Enable clock for USB device */
			clk_enable(udc->clk);
			udc_enable(udc);
		}
	} else {
		if (udc->active) {
			if (udc->gadget.speed != USB_SPEED_UNKNOWN) {
				DMSG("disconnect %s\n", udc->driver
					? udc->driver->driver.name
					: "(no driver)");
				stop_activity(udc, udc->driver);
			}
			udc_disable(udc);
			/* Disable clock for USB device */
			clk_disable(udc->clk);
			udc->active = 0;
		}

	}
	return 0;
}