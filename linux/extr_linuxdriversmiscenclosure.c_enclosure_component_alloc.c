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
struct enclosure_device {unsigned int components; int /*<<< orphan*/  edev; struct enclosure_component* component; } ;
struct device {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct enclosure_component {int number; int type; struct device cdev; } ;
typedef  enum enclosure_component_type { ____Placeholder_enclosure_component_type } enclosure_component_type ;

/* Variables and functions */
 int COMPONENT_NAME_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 struct enclosure_component* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,...) ; 
 scalar_t__ enclosure_component_find_by_name (struct enclosure_device*,char*) ; 
 int /*<<< orphan*/  enclosure_component_groups ; 
 int /*<<< orphan*/  enclosure_component_release ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

struct enclosure_component *
enclosure_component_alloc(struct enclosure_device *edev,
			  unsigned int number,
			  enum enclosure_component_type type,
			  const char *name)
{
	struct enclosure_component *ecomp;
	struct device *cdev;
	int i;
	char newname[COMPONENT_NAME_SIZE];

	if (number >= edev->components)
		return ERR_PTR(-EINVAL);

	ecomp = &edev->component[number];

	if (ecomp->number != -1)
		return ERR_PTR(-EINVAL);

	ecomp->type = type;
	ecomp->number = number;
	cdev = &ecomp->cdev;
	cdev->parent = get_device(&edev->edev);

	if (name && name[0]) {
		/* Some hardware (e.g. enclosure in RX300 S6) has components
		 * with non unique names. Registering duplicates in sysfs
		 * will lead to warnings during bootup. So make the names
		 * unique by appending consecutive numbers -1, -2, ... */
		i = 1;
		snprintf(newname, COMPONENT_NAME_SIZE,
			 "%s", name);
		while (enclosure_component_find_by_name(edev, newname))
			snprintf(newname, COMPONENT_NAME_SIZE,
				 "%s-%i", name, i++);
		dev_set_name(cdev, "%s", newname);
	} else
		dev_set_name(cdev, "%u", number);

	cdev->release = enclosure_component_release;
	cdev->groups = enclosure_component_groups;

	return ecomp;
}