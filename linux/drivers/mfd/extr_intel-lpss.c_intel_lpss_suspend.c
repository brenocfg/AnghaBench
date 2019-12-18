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
struct intel_lpss {scalar_t__ type; scalar_t__ priv; int /*<<< orphan*/ * priv_ctx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPSS_DEV_UART ; 
 unsigned int LPSS_PRIV_REG_COUNT ; 
 scalar_t__ LPSS_PRIV_RESETS ; 
 struct intel_lpss* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int intel_lpss_suspend(struct device *dev)
{
	struct intel_lpss *lpss = dev_get_drvdata(dev);
	unsigned int i;

	/* Save device context */
	for (i = 0; i < LPSS_PRIV_REG_COUNT; i++)
		lpss->priv_ctx[i] = readl(lpss->priv + i * 4);

	/*
	 * If the device type is not UART, then put the controller into
	 * reset. UART cannot be put into reset since S3/S0ix fail when
	 * no_console_suspend flag is enabled.
	 */
	if (lpss->type != LPSS_DEV_UART)
		writel(0, lpss->priv + LPSS_PRIV_RESETS);

	return 0;
}