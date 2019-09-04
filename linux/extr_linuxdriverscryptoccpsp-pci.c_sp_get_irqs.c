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
struct sp_device {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_notice (struct device*,char*,int) ; 
 int sp_get_msi_irq (struct sp_device*) ; 
 int sp_get_msix_irqs (struct sp_device*) ; 

__attribute__((used)) static int sp_get_irqs(struct sp_device *sp)
{
	struct device *dev = sp->dev;
	int ret;

	ret = sp_get_msix_irqs(sp);
	if (!ret)
		return 0;

	/* Couldn't get MSI-X vectors, try MSI */
	dev_notice(dev, "could not enable MSI-X (%d), trying MSI\n", ret);
	ret = sp_get_msi_irq(sp);
	if (!ret)
		return 0;

	/* Couldn't get MSI interrupt */
	dev_notice(dev, "could not enable MSI (%d)\n", ret);

	return ret;
}