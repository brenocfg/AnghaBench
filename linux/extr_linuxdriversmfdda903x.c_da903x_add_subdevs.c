#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  platform_data; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct da903x_subdev_info {int /*<<< orphan*/  platform_data; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct da903x_platform_data {int num_subdevs; struct da903x_subdev_info* subdevs; } ;
struct da903x_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  da903x_remove_subdevs (struct da903x_chip*) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int da903x_add_subdevs(struct da903x_chip *chip,
					struct da903x_platform_data *pdata)
{
	struct da903x_subdev_info *subdev;
	struct platform_device *pdev;
	int i, ret = 0;

	for (i = 0; i < pdata->num_subdevs; i++) {
		subdev = &pdata->subdevs[i];

		pdev = platform_device_alloc(subdev->name, subdev->id);
		if (!pdev) {
			ret = -ENOMEM;
			goto failed;
		}

		pdev->dev.parent = chip->dev;
		pdev->dev.platform_data = subdev->platform_data;

		ret = platform_device_add(pdev);
		if (ret) {
			platform_device_put(pdev);
			goto failed;
		}
	}
	return 0;

failed:
	da903x_remove_subdevs(chip);
	return ret;
}