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
struct asus_laptop {int /*<<< orphan*/  handle; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME_PEGA ; 
 int /*<<< orphan*/  METHOD_PEGA_DISABLE ; 
 int /*<<< orphan*/  METHOD_PEGA_ENABLE ; 
 int /*<<< orphan*/  METHOD_PEGA_READ ; 
 int /*<<< orphan*/  acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool asus_check_pega_lucid(struct asus_laptop *asus)
{
	return !strcmp(asus->name, DEVICE_NAME_PEGA) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_ENABLE, NULL) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_DISABLE, NULL) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_READ, NULL);
}