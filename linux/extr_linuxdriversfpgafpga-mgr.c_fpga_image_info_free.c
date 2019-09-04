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
struct fpga_image_info {struct fpga_image_info* firmware_name; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,struct fpga_image_info*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

void fpga_image_info_free(struct fpga_image_info *info)
{
	struct device *dev;

	if (!info)
		return;

	dev = info->dev;
	if (info->firmware_name)
		devm_kfree(dev, info->firmware_name);

	devm_kfree(dev, info);
	put_device(dev);
}