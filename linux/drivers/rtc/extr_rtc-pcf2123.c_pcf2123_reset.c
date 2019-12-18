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
struct pcf2123_data {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int CTRL1_CLEAR ; 
 unsigned int CTRL1_STOP ; 
 unsigned int CTRL1_SW_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCF2123_REG_CTRL1 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct pcf2123_data* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pcf2123_reset(struct device *dev)
{
	struct pcf2123_data *pcf2123 = dev_get_drvdata(dev);
	int ret;
	unsigned int val = 0;

	ret = regmap_write(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_SW_RESET);
	if (ret)
		return ret;

	/* Stop the counter */
	dev_dbg(dev, "stopping RTC\n");
	ret = regmap_write(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_STOP);
	if (ret)
		return ret;

	/* See if the counter was actually stopped */
	dev_dbg(dev, "checking for presence of RTC\n");
	ret = regmap_read(pcf2123->map, PCF2123_REG_CTRL1, &val);
	if (ret)
		return ret;

	dev_dbg(dev, "received data from RTC (0x%08X)\n", val);
	if (!(val & CTRL1_STOP))
		return -ENODEV;

	/* Start the counter */
	ret = regmap_write(pcf2123->map, PCF2123_REG_CTRL1, CTRL1_CLEAR);
	if (ret)
		return ret;

	return 0;
}