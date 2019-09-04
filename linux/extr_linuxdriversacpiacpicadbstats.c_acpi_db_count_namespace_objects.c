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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_db_classify_one_object ; 
 scalar_t__* acpi_gbl_node_type_count ; 
 scalar_t__ acpi_gbl_num_nodes ; 
 scalar_t__ acpi_gbl_num_objects ; 
 scalar_t__* acpi_gbl_obj_type_count ; 
 scalar_t__ acpi_gbl_obj_type_count_misc ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_db_count_namespace_objects(void)
{
	u32 i;

	acpi_gbl_num_nodes = 0;
	acpi_gbl_num_objects = 0;

	acpi_gbl_obj_type_count_misc = 0;
	for (i = 0; i < (ACPI_TYPE_NS_NODE_MAX - 1); i++) {
		acpi_gbl_obj_type_count[i] = 0;
		acpi_gbl_node_type_count[i] = 0;
	}

	(void)acpi_ns_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, FALSE,
				     acpi_db_classify_one_object, NULL, NULL,
				     NULL);
}