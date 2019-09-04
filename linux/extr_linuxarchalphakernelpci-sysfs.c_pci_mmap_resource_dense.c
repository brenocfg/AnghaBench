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
struct vm_area_struct {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;

/* Variables and functions */
 int pci_mmap_resource (struct kobject*,struct bin_attribute*,struct vm_area_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_mmap_resource_dense(struct file *filp, struct kobject *kobj,
				   struct bin_attribute *attr,
				   struct vm_area_struct *vma)
{
	return pci_mmap_resource(kobj, attr, vma, 0);
}