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
struct hl_device {scalar_t__ pm_mng_profile; struct goya_device* asic_specific; } ;
struct goya_device {long ic_clk; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t EPERM ; 
 int /*<<< orphan*/  IC_PLL ; 
 scalar_t__ PM_AUTO ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  hl_set_frequency (struct hl_device*,int /*<<< orphan*/ ,long) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static ssize_t ic_clk_store(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct hl_device *hdev = dev_get_drvdata(dev);
	struct goya_device *goya = hdev->asic_specific;
	int rc;
	long value;

	if (hl_device_disabled_or_in_reset(hdev)) {
		count = -ENODEV;
		goto fail;
	}

	if (hdev->pm_mng_profile == PM_AUTO) {
		count = -EPERM;
		goto fail;
	}

	rc = kstrtoul(buf, 0, &value);

	if (rc) {
		count = -EINVAL;
		goto fail;
	}

	hl_set_frequency(hdev, IC_PLL, value);
	goya->ic_clk = value;

fail:
	return count;
}