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
struct sun4i_tcon {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun4i_tcon*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_tcon_handler ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sun4i_tcon_init_irq(struct device *dev,
			       struct sun4i_tcon *tcon)
{
	struct platform_device *pdev = to_platform_device(dev);
	int irq, ret;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "Couldn't retrieve the TCON interrupt\n");
		return irq;
	}

	ret = devm_request_irq(dev, irq, sun4i_tcon_handler, 0,
			       dev_name(dev), tcon);
	if (ret) {
		dev_err(dev, "Couldn't request the IRQ\n");
		return ret;
	}

	return 0;
}