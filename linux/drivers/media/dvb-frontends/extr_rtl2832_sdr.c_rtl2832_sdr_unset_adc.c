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
struct rtl2832_sdr_dev {int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl2832_sdr_unset_adc(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;
	int ret;

	dev_dbg(&pdev->dev, "\n");

	/* PID filter */
	ret = regmap_write(dev->regmap, 0x061, 0xe0);
	if (ret)
		goto err;

	/* mode */
	ret = regmap_write(dev->regmap, 0x019, 0x20);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x017, "\x11\x10", 2);
	if (ret)
		goto err;

	/* FSM */
	ret = regmap_bulk_write(dev->regmap, 0x192, "\x00\x0f\xff", 3);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x13e, "\x40\x00", 2);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x115, "\x06\x3f\xce\xcc", 4);
	if (ret)
		goto err;
err:
	return;
}