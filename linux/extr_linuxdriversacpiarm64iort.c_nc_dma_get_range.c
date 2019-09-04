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
typedef  unsigned long long u64 ;
struct device {int dummy; } ;
struct acpi_iort_node {scalar_t__ node_data; } ;
struct acpi_iort_named_component {int memory_address_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IORT_NODE_NAMED_COMPONENT ; 
 int ENODEV ; 
 unsigned long long U64_MAX ; 
 int /*<<< orphan*/  iort_match_node_callback ; 
 struct acpi_iort_node* iort_scan_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int nc_dma_get_range(struct device *dev, u64 *size)
{
	struct acpi_iort_node *node;
	struct acpi_iort_named_component *ncomp;

	node = iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
			      iort_match_node_callback, dev);
	if (!node)
		return -ENODEV;

	ncomp = (struct acpi_iort_named_component *)node->node_data;

	*size = ncomp->memory_address_limit >= 64 ? U64_MAX :
			1ULL<<ncomp->memory_address_limit;

	return 0;
}