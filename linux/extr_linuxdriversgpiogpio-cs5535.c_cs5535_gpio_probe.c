#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip; int /*<<< orphan*/  lock; struct platform_device* pdev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 TYPE_1__ cs5535_gpio_chip ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mask ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs5535_gpio_probe(struct platform_device *pdev)
{
	struct resource *res;
	int err = -EIO;
	ulong mask_orig = mask;

	/* There are two ways to get the GPIO base address; one is by
	 * fetching it from MSR_LBAR_GPIO, the other is by reading the
	 * PCI BAR info.  The latter method is easier (especially across
	 * different architectures), so we'll stick with that for now.  If
	 * it turns out to be unreliable in the face of crappy BIOSes, we
	 * can always go back to using MSRs.. */

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		return err;
	}

	if (!devm_request_region(&pdev->dev, res->start, resource_size(res),
				 pdev->name)) {
		dev_err(&pdev->dev, "can't request region\n");
		return err;
	}

	/* set up the driver-specific struct */
	cs5535_gpio_chip.base = res->start;
	cs5535_gpio_chip.pdev = pdev;
	spin_lock_init(&cs5535_gpio_chip.lock);

	dev_info(&pdev->dev, "reserved resource region %pR\n", res);

	/* mask out reserved pins */
	mask &= 0x1F7FFFFF;

	/* do not allow pin 28, Power Button, as there's special handling
	 * in the PMC needed. (note 12, p. 48) */
	mask &= ~(1 << 28);

	if (mask_orig != mask)
		dev_info(&pdev->dev, "mask changed from 0x%08lX to 0x%08lX\n",
				mask_orig, mask);

	/* finally, register with the generic GPIO API */
	err = devm_gpiochip_add_data(&pdev->dev, &cs5535_gpio_chip.chip,
				     &cs5535_gpio_chip);
	if (err)
		return err;

	return 0;
}