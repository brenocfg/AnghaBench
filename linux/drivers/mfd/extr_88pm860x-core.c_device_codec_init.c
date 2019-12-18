#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pm860x_platform_data {int dummy; } ;
struct pm860x_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct TYPE_6__* resources; int /*<<< orphan*/  num_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* codec_devs ; 
 TYPE_1__* codec_resources ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_codec_init(struct pm860x_chip *chip,
					struct pm860x_platform_data *pdata)
{
	int ret;

	codec_devs[0].num_resources = ARRAY_SIZE(codec_resources);
	codec_devs[0].resources = &codec_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &codec_devs[0],
			      ARRAY_SIZE(codec_devs), &codec_resources[0], 0,
			      NULL);
	if (ret < 0)
		dev_err(chip->dev, "Failed to add codec subdev\n");
}