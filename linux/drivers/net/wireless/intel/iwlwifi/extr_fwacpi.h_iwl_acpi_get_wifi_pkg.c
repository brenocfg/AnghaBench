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
typedef  union acpi_object {int dummy; } acpi_object ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 union acpi_object* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline union acpi_object *iwl_acpi_get_wifi_pkg(struct device *dev,
						       union acpi_object *data,
						       int data_size,
						       int *tbl_rev)
{
	return ERR_PTR(-ENOENT);
}