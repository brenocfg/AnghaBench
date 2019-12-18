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
struct intel_lpss {scalar_t__ priv; int /*<<< orphan*/ * priv_ctx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int LPSS_PRIV_REG_COUNT ; 
 struct intel_lpss* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  intel_lpss_deassert_reset (struct intel_lpss*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int intel_lpss_resume(struct device *dev)
{
	struct intel_lpss *lpss = dev_get_drvdata(dev);
	unsigned int i;

	intel_lpss_deassert_reset(lpss);

	/* Restore device context */
	for (i = 0; i < LPSS_PRIV_REG_COUNT; i++)
		writel(lpss->priv_ctx[i], lpss->priv + i * 4);

	return 0;
}