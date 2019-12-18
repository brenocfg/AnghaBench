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
struct axp20x_usb_power {void* vbus_i; void* vbus_v; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_iio_channel_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int configure_iio_channels(struct platform_device *pdev,
				  struct axp20x_usb_power *power)
{
	power->vbus_v = devm_iio_channel_get(&pdev->dev, "vbus_v");
	if (IS_ERR(power->vbus_v)) {
		if (PTR_ERR(power->vbus_v) == -ENODEV)
			return -EPROBE_DEFER;
		return PTR_ERR(power->vbus_v);
	}

	power->vbus_i = devm_iio_channel_get(&pdev->dev, "vbus_i");
	if (IS_ERR(power->vbus_i)) {
		if (PTR_ERR(power->vbus_i) == -ENODEV)
			return -EPROBE_DEFER;
		return PTR_ERR(power->vbus_i);
	}

	return 0;
}