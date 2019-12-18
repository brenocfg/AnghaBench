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
struct gpio_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_gpiochip_find ; 
 struct gpio_chip* gpiochip_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,int) ; 

__attribute__((used)) static struct gpio_desc *acpi_get_gpiod(char *path, int pin)
{
	struct gpio_chip *chip;
	acpi_handle handle;
	acpi_status status;

	status = acpi_get_handle(NULL, path, &handle);
	if (ACPI_FAILURE(status))
		return ERR_PTR(-ENODEV);

	chip = gpiochip_find(handle, acpi_gpiochip_find);
	if (!chip)
		return ERR_PTR(-EPROBE_DEFER);

	return gpiochip_get_desc(chip, pin);
}