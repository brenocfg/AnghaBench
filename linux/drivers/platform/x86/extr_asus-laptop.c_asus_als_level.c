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
struct asus_laptop {int light_level; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_ALS_LEVEL ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asus_als_level(struct asus_laptop *asus, int value)
{
	if (write_acpi_int(asus->handle, METHOD_ALS_LEVEL, value))
		pr_warn("Error setting light sensor level\n");
	asus->light_level = value;
}