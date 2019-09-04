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
struct aspeed_lpc_snoop {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  aspeed_lpc_snoop_irq ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aspeed_lpc_snoop*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_lpc_snoop_config_irq(struct aspeed_lpc_snoop *lpc_snoop,
				       struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int rc;

	lpc_snoop->irq = platform_get_irq(pdev, 0);
	if (!lpc_snoop->irq)
		return -ENODEV;

	rc = devm_request_irq(dev, lpc_snoop->irq,
			      aspeed_lpc_snoop_irq, IRQF_SHARED,
			      DEVICE_NAME, lpc_snoop);
	if (rc < 0) {
		dev_warn(dev, "Unable to request IRQ %d\n", lpc_snoop->irq);
		lpc_snoop->irq = 0;
		return rc;
	}

	return 0;
}