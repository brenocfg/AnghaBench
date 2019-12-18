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
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 scalar_t__ isl1208_i2c_set_usr (int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
isl1208_sysfs_store_usr(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t count)
{
	int usr = -1;

	if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X')) {
		if (sscanf(buf, "%x", &usr) != 1)
			return -EINVAL;
	} else {
		if (sscanf(buf, "%d", &usr) != 1)
			return -EINVAL;
	}

	if (usr < 0 || usr > 0xffff)
		return -EINVAL;

	if (isl1208_i2c_set_usr(to_i2c_client(dev->parent), usr))
		return -EIO;

	return count;
}