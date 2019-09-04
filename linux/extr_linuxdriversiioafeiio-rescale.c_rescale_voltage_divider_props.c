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
typedef  int /*<<< orphan*/  u32 ;
struct rescale {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rescale_voltage_divider_props(struct device *dev,
					 struct rescale *rescale)
{
	int ret;
	u32 factor;

	ret = device_property_read_u32(dev, "output-ohms",
				       &rescale->denominator);
	if (ret) {
		dev_err(dev, "failed to read output-ohms: %d\n", ret);
		return ret;
	}

	ret = device_property_read_u32(dev, "full-ohms",
				       &rescale->numerator);
	if (ret) {
		dev_err(dev, "failed to read full-ohms: %d\n", ret);
		return ret;
	}

	factor = gcd(rescale->numerator, rescale->denominator);
	rescale->numerator /= factor;
	rescale->denominator /= factor;

	return 0;
}