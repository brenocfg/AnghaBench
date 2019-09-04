#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {union acpi_parse_object* parent; union acpi_parse_object* next; } ;
union acpi_parse_object {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ASL_CV_LABEL_FILENODE (union acpi_parse_object*) ; 
 union acpi_parse_object* acpi_ps_get_arg (union acpi_parse_object*,int /*<<< orphan*/ ) ; 

union acpi_parse_object *acpi_ps_get_depth_next(union acpi_parse_object *origin,
						union acpi_parse_object *op)
{
	union acpi_parse_object *next = NULL;
	union acpi_parse_object *parent;
	union acpi_parse_object *arg;

	ACPI_FUNCTION_ENTRY();

	if (!op) {
		return (NULL);
	}

	/* Look for an argument or child */

	next = acpi_ps_get_arg(op, 0);
	if (next) {
		ASL_CV_LABEL_FILENODE(next);
		return (next);
	}

	/* Look for a sibling */

	next = op->common.next;
	if (next) {
		ASL_CV_LABEL_FILENODE(next);
		return (next);
	}

	/* Look for a sibling of parent */

	parent = op->common.parent;

	while (parent) {
		arg = acpi_ps_get_arg(parent, 0);
		while (arg && (arg != origin) && (arg != op)) {

			ASL_CV_LABEL_FILENODE(arg);
			arg = arg->common.next;
		}

		if (arg == origin) {

			/* Reached parent of origin, end search */

			return (NULL);
		}

		if (parent->common.next) {

			/* Found sibling of parent */

			ASL_CV_LABEL_FILENODE(parent->common.next);
			return (parent->common.next);
		}

		op = parent;
		parent = parent->common.parent;
	}

	ASL_CV_LABEL_FILENODE(next);
	return (next);
}