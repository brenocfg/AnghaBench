#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* driver; } ;
struct serdev_device {struct device dev; } ;
struct h5_vnd {scalar_t__ acpi_gpio_map; } ;
struct TYPE_4__ {struct serdev_device* serdev; int /*<<< orphan*/  flags; } ;
struct h5 {char* id; TYPE_2__ serdev_hu; void* device_wake_gpio; void* enable_gpio; struct h5_vnd const* vnd; TYPE_2__* hu; } ;
struct acpi_device_id {scalar_t__ id; scalar_t__ driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  HCI_UART_RESET_ON_INIT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  devm_acpi_dev_add_driver_gpios (struct device*,scalar_t__) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct h5* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h5p ; 
 scalar_t__ has_acpi_companion (struct device*) ; 
 int hci_uart_register_device (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct h5*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h5_serdev_probe(struct serdev_device *serdev)
{
	const struct acpi_device_id *match;
	struct device *dev = &serdev->dev;
	struct h5 *h5;

	h5 = devm_kzalloc(dev, sizeof(*h5), GFP_KERNEL);
	if (!h5)
		return -ENOMEM;

	set_bit(HCI_UART_RESET_ON_INIT, &h5->serdev_hu.flags);

	h5->hu = &h5->serdev_hu;
	h5->serdev_hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, h5);

	if (has_acpi_companion(dev)) {
		match = acpi_match_device(dev->driver->acpi_match_table, dev);
		if (!match)
			return -ENODEV;

		h5->vnd = (const struct h5_vnd *)match->driver_data;
		h5->id  = (char *)match->id;

		if (h5->vnd->acpi_gpio_map)
			devm_acpi_dev_add_driver_gpios(dev,
						       h5->vnd->acpi_gpio_map);
	}

	h5->enable_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(h5->enable_gpio))
		return PTR_ERR(h5->enable_gpio);

	h5->device_wake_gpio = devm_gpiod_get_optional(dev, "device-wake",
						       GPIOD_OUT_LOW);
	if (IS_ERR(h5->device_wake_gpio))
		return PTR_ERR(h5->device_wake_gpio);

	return hci_uart_register_device(&h5->serdev_hu, &h5p);
}