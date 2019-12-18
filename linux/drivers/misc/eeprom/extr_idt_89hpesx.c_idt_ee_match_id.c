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
struct i2c_device_id {scalar_t__* name; } ;
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  devname ;

/* Variables and functions */
 int I2C_NAME_SIZE ; 
 struct i2c_device_id* ee_ids ; 
 int fwnode_property_read_string (struct fwnode_handle*,char*,char const**) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,scalar_t__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static const struct i2c_device_id *idt_ee_match_id(struct fwnode_handle *fwnode)
{
	const struct i2c_device_id *id = ee_ids;
	const char *compatible, *p;
	char devname[I2C_NAME_SIZE];
	int ret;

	ret = fwnode_property_read_string(fwnode, "compatible", &compatible);
	if (ret)
		return NULL;

	p = strchr(compatible, ',');
	strlcpy(devname, p ? p + 1 : compatible, sizeof(devname));
	/* Search through the device name */
	while (id->name[0]) {
		if (strcmp(devname, id->name) == 0)
			return id;
		id++;
	}
	return NULL;
}