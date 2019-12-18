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
struct xwdt_device {int /*<<< orphan*/  spinlock; scalar_t__ base; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int XWT_CSR0_WDS_MASK ; 
 int XWT_CSR0_WRS_MASK ; 
 scalar_t__ XWT_TWCSR0_OFFSET ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct xwdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int xilinx_wdt_keepalive(struct watchdog_device *wdd)
{
	u32 control_status_reg;
	struct xwdt_device *xdev = watchdog_get_drvdata(wdd);

	spin_lock(&xdev->spinlock);

	control_status_reg = ioread32(xdev->base + XWT_TWCSR0_OFFSET);
	control_status_reg |= (XWT_CSR0_WRS_MASK | XWT_CSR0_WDS_MASK);
	iowrite32(control_status_reg, xdev->base + XWT_TWCSR0_OFFSET);

	spin_unlock(&xdev->spinlock);

	return 0;
}