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
typedef  int u32 ;
struct rescale {int numerator; int denominator; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int gcd (int,int) ; 

__attribute__((used)) static int rescale_current_sense_shunt_props(struct device *dev,
					     struct rescale *rescale)
{
	u32 shunt;
	u32 factor;
	int ret;

	ret = device_property_read_u32(dev, "shunt-resistor-micro-ohms",
				       &shunt);
	if (ret) {
		dev_err(dev, "failed to read the shunt resistance: %d\n", ret);
		return ret;
	}

	factor = gcd(shunt, 1000000);
	rescale->numerator = 1000000 / factor;
	rescale->denominator = shunt / factor;

	return 0;
}