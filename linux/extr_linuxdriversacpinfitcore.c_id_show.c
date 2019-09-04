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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_nfit_control_region {int valid_fields; int manufacturing_location; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  manufacturing_date; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ACPI_NFIT_CONTROL_MFG_INFO_VALID ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 
 struct acpi_nfit_control_region* to_nfit_dcr (struct device*) ; 

__attribute__((used)) static ssize_t id_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	if (dcr->valid_fields & ACPI_NFIT_CONTROL_MFG_INFO_VALID)
		return sprintf(buf, "%04x-%02x-%04x-%08x\n",
				be16_to_cpu(dcr->vendor_id),
				dcr->manufacturing_location,
				be16_to_cpu(dcr->manufacturing_date),
				be32_to_cpu(dcr->serial_number));
	else
		return sprintf(buf, "%04x-%08x\n",
				be16_to_cpu(dcr->vendor_id),
				be32_to_cpu(dcr->serial_number));
}