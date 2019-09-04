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
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_ns_build_normalized_path (struct acpi_namespace_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

acpi_size acpi_ns_get_pathname_length(struct acpi_namespace_node *node)
{
	acpi_size size;

	/* Validate the Node */

	if (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) {
		ACPI_ERROR((AE_INFO,
			    "Invalid/cached reference target node: %p, descriptor type %d",
			    node, ACPI_GET_DESCRIPTOR_TYPE(node)));
		return (0);
	}

	size = acpi_ns_build_normalized_path(node, NULL, 0, FALSE);
	return (size);
}