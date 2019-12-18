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
struct asus_laptop {int light_switch; int /*<<< orphan*/  handle; scalar_t__ is_pega_lucid; } ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_ALS_CONTROL ; 
 int /*<<< orphan*/  PEGA_ALS ; 
 int /*<<< orphan*/  PEGA_ALS_POWER ; 
 int asus_pega_lucid_set (struct asus_laptop*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asus_als_switch(struct asus_laptop *asus, int value)
{
	int ret;

	if (asus->is_pega_lucid) {
		ret = asus_pega_lucid_set(asus, PEGA_ALS, value);
		if (!ret)
			ret = asus_pega_lucid_set(asus, PEGA_ALS_POWER, value);
	} else {
		ret = write_acpi_int(asus->handle, METHOD_ALS_CONTROL, value);
	}
	if (ret)
		pr_warning("Error setting light sensor switch\n");

	asus->light_switch = value;
}