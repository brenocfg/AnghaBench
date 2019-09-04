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
struct kobject {int dummy; } ;
struct edac_device_ctl_info {int dummy; } ;
struct ctl_info_attribute {int /*<<< orphan*/  (* show ) (struct edac_device_ctl_info*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct edac_device_ctl_info*,char*) ; 
 struct edac_device_ctl_info* to_ctl_info (struct kobject*) ; 
 struct ctl_info_attribute* to_ctl_info_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t edac_dev_ctl_info_show(struct kobject *kobj,
				struct attribute *attr, char *buffer)
{
	struct edac_device_ctl_info *edac_dev = to_ctl_info(kobj);
	struct ctl_info_attribute *ctl_info_attr = to_ctl_info_attr(attr);

	if (ctl_info_attr->show)
		return ctl_info_attr->show(edac_dev, buffer);
	return -EIO;
}