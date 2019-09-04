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
typedef  int /*<<< orphan*/  u32 ;
struct rpi_firmware {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_GET_THROTTLED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ devm_device_add_group (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpi_firmware_dev_group ; 
 int rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rpi_hwmon ; 

__attribute__((used)) static void
rpi_register_hwmon_driver(struct device *dev, struct rpi_firmware *fw)
{
	u32 packet;
	int ret = rpi_firmware_property(fw, RPI_FIRMWARE_GET_THROTTLED,
					&packet, sizeof(packet));

	if (ret)
		return;

	rpi_hwmon = platform_device_register_data(dev, "raspberrypi-hwmon",
						  -1, NULL, 0);

	if (!IS_ERR_OR_NULL(rpi_hwmon)) {
		if (devm_device_add_group(dev, &rpi_firmware_dev_group))
			dev_err(dev, "Failed to create get_trottled attr\n");
	}
}