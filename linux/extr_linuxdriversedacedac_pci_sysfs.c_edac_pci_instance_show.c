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
struct instance_attribute {int /*<<< orphan*/  (* show ) (struct edac_pci_ctl_info*,char*) ;} ;
struct edac_pci_ctl_info {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct edac_pci_ctl_info*,char*) ; 
 struct edac_pci_ctl_info* to_instance (struct kobject*) ; 
 struct instance_attribute* to_instance_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t edac_pci_instance_show(struct kobject *kobj,
				struct attribute *attr, char *buffer)
{
	struct edac_pci_ctl_info *pci = to_instance(kobj);
	struct instance_attribute *instance_attr = to_instance_attr(attr);

	if (instance_attr->show)
		return instance_attr->show(pci, buffer);
	return -EIO;
}