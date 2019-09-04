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
struct input_dev {int dummy; } ;
struct drv260x_data {int /*<<< orphan*/  enable_gpio; TYPE_1__* client; int /*<<< orphan*/  regmap; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV260X_MODE ; 
 int /*<<< orphan*/  DRV260X_STANDBY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drv260x_data* input_get_drvdata (struct input_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drv260x_close(struct input_dev *input)
{
	struct drv260x_data *haptics = input_get_drvdata(input);
	int error;

	cancel_work_sync(&haptics->work);

	error = regmap_write(haptics->regmap, DRV260X_MODE, DRV260X_STANDBY);
	if (error)
		dev_err(&haptics->client->dev,
			"Failed to enter standby mode: %d\n", error);

	gpiod_set_value(haptics->enable_gpio, 0);
}