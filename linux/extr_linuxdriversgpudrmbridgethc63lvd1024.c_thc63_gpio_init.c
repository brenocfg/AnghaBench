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
struct thc63_dev {void* pdwn; int /*<<< orphan*/  dev; void* oe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thc63_gpio_init(struct thc63_dev *thc63)
{
	thc63->oe = devm_gpiod_get_optional(thc63->dev, "oe", GPIOD_OUT_LOW);
	if (IS_ERR(thc63->oe)) {
		dev_err(thc63->dev, "Unable to get \"oe-gpios\": %ld\n",
			PTR_ERR(thc63->oe));
		return PTR_ERR(thc63->oe);
	}

	thc63->pdwn = devm_gpiod_get_optional(thc63->dev, "powerdown",
					      GPIOD_OUT_HIGH);
	if (IS_ERR(thc63->pdwn)) {
		dev_err(thc63->dev, "Unable to get \"powerdown-gpios\": %ld\n",
			PTR_ERR(thc63->pdwn));
		return PTR_ERR(thc63->pdwn);
	}

	return 0;
}