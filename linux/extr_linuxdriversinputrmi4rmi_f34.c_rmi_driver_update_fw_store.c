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
struct rmi_driver_data {int dummy; } ;
struct firmware {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int NAME_MAX ; 
 struct rmi_driver_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 
 int rmi_firmware_update (struct rmi_driver_data*,struct firmware const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static ssize_t rmi_driver_update_fw_store(struct device *dev,
					  struct device_attribute *dattr,
					  const char *buf, size_t count)
{
	struct rmi_driver_data *data = dev_get_drvdata(dev);
	char fw_name[NAME_MAX];
	const struct firmware *fw;
	size_t copy_count = count;
	int ret;

	if (count == 0 || count >= NAME_MAX)
		return -EINVAL;

	if (buf[count - 1] == '\0' || buf[count - 1] == '\n')
		copy_count -= 1;

	strncpy(fw_name, buf, copy_count);
	fw_name[copy_count] = '\0';

	ret = request_firmware(&fw, fw_name, dev);
	if (ret)
		return ret;

	dev_info(dev, "Flashing %s\n", fw_name);

	ret = rmi_firmware_update(data, fw);

	release_firmware(fw);

	return ret ?: count;
}