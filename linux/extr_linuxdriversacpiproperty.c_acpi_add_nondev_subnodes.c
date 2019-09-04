#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; union acpi_object* elements; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
union acpi_object {int type; TYPE_2__ package; TYPE_1__ reference; } ;
struct list_head {int dummy; } ;
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_TYPE_LOCAL_REFERENCE 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int acpi_nondev_subnode_data_ok (int /*<<< orphan*/ ,union acpi_object const*,struct list_head*,struct fwnode_handle*) ; 
 int acpi_nondev_subnode_extract (union acpi_object const*,int /*<<< orphan*/ *,union acpi_object const*,struct list_head*,struct fwnode_handle*) ; 
 int acpi_nondev_subnode_ok (int /*<<< orphan*/ ,union acpi_object const*,struct list_head*,struct fwnode_handle*) ; 

__attribute__((used)) static int acpi_add_nondev_subnodes(acpi_handle scope,
				    const union acpi_object *links,
				    struct list_head *list,
				    struct fwnode_handle *parent)
{
	bool ret = false;
	int i;

	for (i = 0; i < links->package.count; i++) {
		const union acpi_object *link, *desc;
		acpi_handle handle;
		bool result;

		link = &links->package.elements[i];
		/* Only two elements allowed. */
		if (link->package.count != 2)
			continue;

		/* The first one must be a string. */
		if (link->package.elements[0].type != ACPI_TYPE_STRING)
			continue;

		/* The second one may be a string, a reference or a package. */
		switch (link->package.elements[1].type) {
		case ACPI_TYPE_STRING:
			result = acpi_nondev_subnode_ok(scope, link, list,
							 parent);
			break;
		case ACPI_TYPE_LOCAL_REFERENCE:
			handle = link->package.elements[1].reference.handle;
			result = acpi_nondev_subnode_data_ok(handle, link, list,
							     parent);
			break;
		case ACPI_TYPE_PACKAGE:
			desc = &link->package.elements[1];
			result = acpi_nondev_subnode_extract(desc, NULL, link,
							     list, parent);
			break;
		default:
			result = false;
			break;
		}
		ret = ret || result;
	}

	return ret;
}