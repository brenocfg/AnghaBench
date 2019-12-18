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
struct pci_slot_attribute {int /*<<< orphan*/  (* store ) (struct pci_slot*,char const*,size_t) ;} ;
struct pci_slot {int dummy; } ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct pci_slot*,char const*,size_t) ; 
 struct pci_slot* to_pci_slot (struct kobject*) ; 
 struct pci_slot_attribute* to_pci_slot_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t pci_slot_attr_store(struct kobject *kobj,
			struct attribute *attr, const char *buf, size_t len)
{
	struct pci_slot *slot = to_pci_slot(kobj);
	struct pci_slot_attribute *attribute = to_pci_slot_attr(attr);
	return attribute->store ? attribute->store(slot, buf, len) : -EIO;
}