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
struct ipmi_device_id {int* aux_firmware_revision; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bmc_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int bmc_get_device_id (int /*<<< orphan*/ *,struct bmc_device*,struct ipmi_device_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,int,int,int,int) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static ssize_t aux_firmware_rev_show(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct bmc_device *bmc = to_bmc_device(dev);
	struct ipmi_device_id id;
	int rv;

	rv = bmc_get_device_id(NULL, bmc, &id, NULL, NULL);
	if (rv)
		return rv;

	return snprintf(buf, 21, "0x%02x 0x%02x 0x%02x 0x%02x\n",
			id.aux_firmware_revision[3],
			id.aux_firmware_revision[2],
			id.aux_firmware_revision[1],
			id.aux_firmware_revision[0]);
}