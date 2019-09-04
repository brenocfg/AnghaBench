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
struct acpi_nfit_control_region {int /*<<< orphan*/  revision_id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct acpi_nfit_control_region* to_nfit_dcr (struct device*) ; 

__attribute__((used)) static ssize_t rev_id_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	return sprintf(buf, "0x%04x\n", be16_to_cpu(dcr->revision_id));
}