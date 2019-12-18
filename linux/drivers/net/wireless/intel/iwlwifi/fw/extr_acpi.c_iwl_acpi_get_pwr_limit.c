#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* elements; } ;
union acpi_object {TYPE_3__ package; } ;
typedef  scalar_t__ u64 ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SPLC_METHOD ; 
 int /*<<< orphan*/  ACPI_SPLC_WIFI_DATA_SIZE ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ IS_ERR (union acpi_object*) ; 
 union acpi_object* iwl_acpi_get_object (struct device*,int /*<<< orphan*/ ) ; 
 union acpi_object* iwl_acpi_get_wifi_pkg (struct device*,union acpi_object*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

u64 iwl_acpi_get_pwr_limit(struct device *dev)
{
	union acpi_object *data, *wifi_pkg;
	u64 dflt_pwr_limit;
	int tbl_rev;

	data = iwl_acpi_get_object(dev, ACPI_SPLC_METHOD);
	if (IS_ERR(data)) {
		dflt_pwr_limit = 0;
		goto out;
	}

	wifi_pkg = iwl_acpi_get_wifi_pkg(dev, data,
					 ACPI_SPLC_WIFI_DATA_SIZE, &tbl_rev);
	if (IS_ERR(wifi_pkg) || tbl_rev != 0 ||
	    wifi_pkg->package.elements[1].integer.value != ACPI_TYPE_INTEGER) {
		dflt_pwr_limit = 0;
		goto out_free;
	}

	dflt_pwr_limit = wifi_pkg->package.elements[1].integer.value;
out_free:
	kfree(data);
out:
	return dflt_pwr_limit;
}