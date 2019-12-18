#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device_id {int driver_data; } ;
struct TYPE_6__ {struct it913x_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct it913x_platform_data {int /*<<< orphan*/  role; struct dvb_frontend* fe; int /*<<< orphan*/  regmap; } ;
struct it913x_dev {int chip_ver; int /*<<< orphan*/  role; struct dvb_frontend* fe; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct it913x_dev* tuner_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  it913x_tuner_ops ; 
 struct it913x_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct it913x_dev*) ; 

__attribute__((used)) static int it913x_probe(struct platform_device *pdev)
{
	struct it913x_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_frontend *fe = pdata->fe;
	struct it913x_dev *dev;
	const struct platform_device_id *id = platform_get_device_id(pdev);
	int ret;
	char *chip_ver_str;

	dev = kzalloc(sizeof(struct it913x_dev), GFP_KERNEL);
	if (dev == NULL) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "kzalloc() failed\n");
		goto err;
	}

	dev->pdev = pdev;
	dev->regmap = pdata->regmap;
	dev->fe = pdata->fe;
	dev->chip_ver = id->driver_data;
	dev->role = pdata->role;

	fe->tuner_priv = dev;
	memcpy(&fe->ops.tuner_ops, &it913x_tuner_ops,
			sizeof(struct dvb_tuner_ops));
	platform_set_drvdata(pdev, dev);

	if (dev->chip_ver == 1)
		chip_ver_str = "AX";
	else if (dev->chip_ver == 2)
		chip_ver_str = "BX";
	else
		chip_ver_str = "??";

	dev_info(&pdev->dev, "ITE IT913X %s successfully attached\n",
		 chip_ver_str);
	dev_dbg(&pdev->dev, "chip_ver %u, role %u\n", dev->chip_ver, dev->role);
	return 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	return ret;
}