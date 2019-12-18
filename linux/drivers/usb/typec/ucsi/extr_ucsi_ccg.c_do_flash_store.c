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
struct ucsi_ccg {int fw_build; int /*<<< orphan*/  work; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct ucsi_ccg* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t do_flash_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t n)
{
	struct ucsi_ccg *uc = i2c_get_clientdata(to_i2c_client(dev));
	bool flash;

	if (kstrtobool(buf, &flash))
		return -EINVAL;

	if (!flash)
		return n;

	if (uc->fw_build == 0x0) {
		dev_err(dev, "fail to flash FW due to missing FW build info\n");
		return -EINVAL;
	}

	schedule_work(&uc->work);
	return n;
}