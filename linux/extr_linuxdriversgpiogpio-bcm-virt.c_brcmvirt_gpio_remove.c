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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct brcmvirt_gpio {scalar_t__ ts_base; scalar_t__ bus_addr; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct brcmvirt_gpio* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int brcmvirt_gpio_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int err = 0;
	struct brcmvirt_gpio *ucb = platform_get_drvdata(pdev);

	gpiochip_remove(&ucb->gc);
	if (ucb->bus_addr)
		dma_free_coherent(dev, PAGE_SIZE, ucb->ts_base, ucb->bus_addr);
	else if (ucb->ts_base)
		iounmap(ucb->ts_base);
	return err;
}