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
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_4__ {int value; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ integer; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_WRDD_METHOD ; 
 int /*<<< orphan*/  ACPI_WRDD_WIFI_DATA_SIZE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (union acpi_object*) ; 
 int PTR_ERR (union acpi_object*) ; 
 union acpi_object* iwl_acpi_get_object (struct device*,int /*<<< orphan*/ ) ; 
 union acpi_object* iwl_acpi_get_wifi_pkg (struct device*,union acpi_object*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

int iwl_acpi_get_mcc(struct device *dev, char *mcc)
{
	union acpi_object *wifi_pkg, *data;
	u32 mcc_val;
	int ret, tbl_rev;

	data = iwl_acpi_get_object(dev, ACPI_WRDD_METHOD);
	if (IS_ERR(data))
		return PTR_ERR(data);

	wifi_pkg = iwl_acpi_get_wifi_pkg(dev, data, ACPI_WRDD_WIFI_DATA_SIZE,
					 &tbl_rev);
	if (IS_ERR(wifi_pkg)) {
		ret = PTR_ERR(wifi_pkg);
		goto out_free;
	}

	if (wifi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER ||
	    tbl_rev != 0) {
		ret = -EINVAL;
		goto out_free;
	}

	mcc_val = wifi_pkg->package.elements[1].integer.value;

	mcc[0] = (mcc_val >> 8) & 0xff;
	mcc[1] = mcc_val & 0xff;
	mcc[2] = '\0';

	ret = 0;
out_free:
	kfree(data);
	return ret;
}