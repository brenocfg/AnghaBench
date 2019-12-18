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
struct ishtp_cl_data {int /*<<< orphan*/  cl_device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_property_read_string (struct device*,char*,char const**) ; 
 struct device* ishtp_get_pci_device (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int get_firmware_variant(struct ishtp_cl_data *client_data,
				char *filename)
{
	int rv;
	const char *val;
	struct device *devc = ishtp_get_pci_device(client_data->cl_device);

	rv = device_property_read_string(devc, "firmware-name", &val);
	if (rv < 0) {
		dev_err(devc,
			"Error: ISH firmware-name device property required\n");
		return rv;
	}
	return snprintf(filename, FILENAME_SIZE, "intel/%s", val);
}