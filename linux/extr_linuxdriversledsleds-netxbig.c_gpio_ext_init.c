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
struct netxbig_gpio_ext {int num_addr; int num_data; int /*<<< orphan*/  enable; int /*<<< orphan*/ * data; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gpio_ext_init(struct platform_device *pdev,
			 struct netxbig_gpio_ext *gpio_ext)
{
	int err;
	int i;

	if (unlikely(!gpio_ext))
		return -EINVAL;

	/* Configure address GPIOs. */
	for (i = 0; i < gpio_ext->num_addr; i++) {
		err = devm_gpio_request_one(&pdev->dev, gpio_ext->addr[i],
					    GPIOF_OUT_INIT_LOW,
					    "GPIO extension addr");
		if (err)
			return err;
	}
	/* Configure data GPIOs. */
	for (i = 0; i < gpio_ext->num_data; i++) {
		err = devm_gpio_request_one(&pdev->dev, gpio_ext->data[i],
					    GPIOF_OUT_INIT_LOW,
					    "GPIO extension data");
		if (err)
			return err;
	}
	/* Configure "enable select" GPIO. */
	err = devm_gpio_request_one(&pdev->dev, gpio_ext->enable,
				    GPIOF_OUT_INIT_LOW,
				    "GPIO extension enable");
	if (err)
		return err;

	return 0;
}