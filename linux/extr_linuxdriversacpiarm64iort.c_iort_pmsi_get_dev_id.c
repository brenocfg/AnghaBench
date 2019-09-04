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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct acpi_iort_node {int mapping_count; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORT_MSI_TYPE ; 
 struct acpi_iort_node* iort_find_dev_node (struct device*) ; 
 int iort_get_id_mapping_index (struct acpi_iort_node*) ; 
 scalar_t__ iort_node_get_id (struct acpi_iort_node*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ iort_node_map_platform_id (struct acpi_iort_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int iort_pmsi_get_dev_id(struct device *dev, u32 *dev_id)
{
	int i, index;
	struct acpi_iort_node *node;

	node = iort_find_dev_node(dev);
	if (!node)
		return -ENODEV;

	index = iort_get_id_mapping_index(node);
	/* if there is a valid index, go get the dev_id directly */
	if (index >= 0) {
		if (iort_node_get_id(node, dev_id, index))
			return 0;
	} else {
		for (i = 0; i < node->mapping_count; i++) {
			if (iort_node_map_platform_id(node, dev_id,
						      IORT_MSI_TYPE, i))
				return 0;
		}
	}

	return -ENODEV;
}