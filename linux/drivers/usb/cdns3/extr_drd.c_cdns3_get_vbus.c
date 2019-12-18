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
struct cdns3 {int /*<<< orphan*/  dev; TYPE_1__* otg_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  sts; } ;

/* Variables and functions */
 int OTGSTS_VBUS_VALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int readl (int /*<<< orphan*/ *) ; 

int cdns3_get_vbus(struct cdns3 *cdns)
{
	int vbus;

	vbus = !!(readl(&cdns->otg_regs->sts) & OTGSTS_VBUS_VALID);
	dev_dbg(cdns->dev, "OTG VBUS: %d", vbus);

	return vbus;
}