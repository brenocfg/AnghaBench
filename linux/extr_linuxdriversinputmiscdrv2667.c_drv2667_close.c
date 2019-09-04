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
struct drv2667_data {TYPE_1__* client; int /*<<< orphan*/  regmap; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV2667_CTRL_2 ; 
 int /*<<< orphan*/  DRV2667_STANDBY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct drv2667_data* input_get_drvdata (struct input_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drv2667_close(struct input_dev *input)
{
	struct drv2667_data *haptics = input_get_drvdata(input);
	int error;

	cancel_work_sync(&haptics->work);

	error = regmap_update_bits(haptics->regmap, DRV2667_CTRL_2,
				   DRV2667_STANDBY, DRV2667_STANDBY);
	if (error)
		dev_err(&haptics->client->dev,
			"Failed to enter standby mode: %d\n", error);
}