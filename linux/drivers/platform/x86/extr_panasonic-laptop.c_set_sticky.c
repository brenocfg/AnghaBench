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
struct pcc_acpi {int sticky_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SINF_STICKY_KEY ; 
 struct pcc_acpi* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_pcc_write_sset (struct pcc_acpi*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t set_sticky(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct acpi_device *acpi = to_acpi_device(dev);
	struct pcc_acpi *pcc = acpi_driver_data(acpi);
	int val;

	if (count && sscanf(buf, "%i", &val) == 1 &&
	    (val == 0 || val == 1)) {
		acpi_pcc_write_sset(pcc, SINF_STICKY_KEY, val);
		pcc->sticky_mode = val;
	}

	return count;
}