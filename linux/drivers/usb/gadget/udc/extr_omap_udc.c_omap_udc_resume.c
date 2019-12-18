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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  omap_pullup (int /*<<< orphan*/ *,int) ; 
 int omap_wakeup (int /*<<< orphan*/ *) ; 
 TYPE_1__* udc ; 

__attribute__((used)) static int omap_udc_resume(struct platform_device *dev)
{
	DBG("resume + wakeup/SRP\n");
	omap_pullup(&udc->gadget, 1);

	/* maybe the host would enumerate us if we nudged it */
	msleep(100);
	return omap_wakeup(&udc->gadget);
}