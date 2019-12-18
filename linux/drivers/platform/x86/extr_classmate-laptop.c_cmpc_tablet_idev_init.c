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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; int /*<<< orphan*/  swbit; int /*<<< orphan*/  evbit; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 int /*<<< orphan*/  cmpc_get_tablet (int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  input_report_switch (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmpc_tablet_idev_init(struct input_dev *inputdev)
{
	unsigned long long val = 0;
	struct acpi_device *acpi;

	set_bit(EV_SW, inputdev->evbit);
	set_bit(SW_TABLET_MODE, inputdev->swbit);

	acpi = to_acpi_device(inputdev->dev.parent);
	if (ACPI_SUCCESS(cmpc_get_tablet(acpi->handle, &val))) {
		input_report_switch(inputdev, SW_TABLET_MODE, !val);
		input_sync(inputdev);
	}
}