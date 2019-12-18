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
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 int OF_ROOT_NODE_SIZE_CELLS_DEFAULT ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

int of_n_size_cells(struct device_node *np)
{
	u32 cells;

	do {
		if (np->parent)
			np = np->parent;
		if (!of_property_read_u32(np, "#size-cells", &cells))
			return cells;
	} while (np->parent);
	/* No #size-cells property for the root node */
	return OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
}