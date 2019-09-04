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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct it913x_dev {int role; int active; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct dvb_frontend {struct it913x_dev* tuner_priv; } ;

/* Variables and functions */
 scalar_t__ IT913X_ROLE_DUAL_MASTER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int it913x_sleep(struct dvb_frontend *fe)
{
	struct it913x_dev *dev = fe->tuner_priv;
	struct platform_device *pdev = dev->pdev;
	int ret, len;

	dev_dbg(&pdev->dev, "role %u\n", dev->role);

	dev->active = false;

	ret  = regmap_bulk_write(dev->regmap, 0x80ec40, "\x00", 1);
	if (ret)
		goto err;

	/*
	 * Writing '0x00' to master tuner register '0x80ec08' causes slave tuner
	 * communication lost. Due to that, we cannot put master full sleep.
	 */
	if (dev->role == IT913X_ROLE_DUAL_MASTER)
		len = 4;
	else
		len = 15;

	dev_dbg(&pdev->dev, "role %u, len %d\n", dev->role, len);

	ret = regmap_bulk_write(dev->regmap, 0x80ec02,
			"\x3f\x1f\x3f\x3e\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
			len);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x80ec12, "\x00\x00\x00\x00", 4);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x80ec17,
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00", 9);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x80ec22,
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x80ec20, "\x00", 1);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x80ec3f, "\x01", 1);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	return ret;
}