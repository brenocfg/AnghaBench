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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int dummy; } ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ acpi_ns_build_normalized_path (struct acpi_namespace_node*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_get_normalized_pathname ; 
 int /*<<< orphan*/  return_PTR (char*) ; 

char *acpi_ns_get_normalized_pathname(struct acpi_namespace_node *node,
				      u8 no_trailing)
{
	char *name_buffer;
	acpi_size size;

	ACPI_FUNCTION_TRACE_PTR(ns_get_normalized_pathname, node);

	/* Calculate required buffer size based on depth below root */

	size = acpi_ns_build_normalized_path(node, NULL, 0, no_trailing);
	if (!size) {
		return_PTR(NULL);
	}

	/* Allocate a buffer to be returned to caller */

	name_buffer = ACPI_ALLOCATE_ZEROED(size);
	if (!name_buffer) {
		ACPI_ERROR((AE_INFO, "Could not allocate %u bytes", (u32)size));
		return_PTR(NULL);
	}

	/* Build the path in the allocated buffer */

	(void)acpi_ns_build_normalized_path(node, name_buffer, size,
					    no_trailing);

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES, "%s: Path \"%s\"\n",
			      ACPI_GET_FUNCTION_NAME, name_buffer));

	return_PTR(name_buffer);
}