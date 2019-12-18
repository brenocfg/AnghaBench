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
typedef  int ssize_t ;

/* Variables and functions */
 int isl1208_i2c_get_usr (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
isl1208_sysfs_show_usr(struct device *dev,
		       struct device_attribute *attr, char *buf)
{
	int usr = isl1208_i2c_get_usr(to_i2c_client(dev->parent));
	if (usr < 0)
		return usr;

	return sprintf(buf, "0x%.4x\n", usr);
}