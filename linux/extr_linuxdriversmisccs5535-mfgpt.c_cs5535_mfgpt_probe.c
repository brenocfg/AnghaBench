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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int initialized; int /*<<< orphan*/  lock; struct platform_device* pdev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 TYPE_1__ cs5535_mfgpt_chip ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int mfgpt_reset_timers ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int scan_timers (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs5535_mfgpt_probe(struct platform_device *pdev)
{
	struct resource *res;
	int err = -EIO, t;

	if (mfgpt_reset_timers < 0 || mfgpt_reset_timers > 2) {
		dev_err(&pdev->dev, "Bad mfgpt_reset_timers value: %i\n",
			mfgpt_reset_timers);
		goto done;
	}

	/* There are two ways to get the MFGPT base address; one is by
	 * fetching it from MSR_LBAR_MFGPT, the other is by reading the
	 * PCI BAR info.  The latter method is easier (especially across
	 * different architectures), so we'll stick with that for now.  If
	 * it turns out to be unreliable in the face of crappy BIOSes, we
	 * can always go back to using MSRs.. */

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		goto done;
	}

	if (!request_region(res->start, resource_size(res), pdev->name)) {
		dev_err(&pdev->dev, "can't request region\n");
		goto done;
	}

	/* set up the driver-specific struct */
	cs5535_mfgpt_chip.base = res->start;
	cs5535_mfgpt_chip.pdev = pdev;
	spin_lock_init(&cs5535_mfgpt_chip.lock);

	dev_info(&pdev->dev, "reserved resource region %pR\n", res);

	/* detect the available timers */
	t = scan_timers(&cs5535_mfgpt_chip);
	dev_info(&pdev->dev, "%d MFGPT timers available\n", t);
	cs5535_mfgpt_chip.initialized = 1;
	return 0;

done:
	return err;
}