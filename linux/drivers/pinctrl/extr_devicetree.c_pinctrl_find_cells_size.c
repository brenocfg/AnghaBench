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
struct device_node {TYPE_1__* parent; } ;
struct TYPE_2__ {struct TYPE_2__* parent; } ;

/* Variables and functions */
 int ENOENT ; 
 int of_property_read_u32 (TYPE_1__*,char const*,int*) ; 

__attribute__((used)) static int pinctrl_find_cells_size(const struct device_node *np)
{
	const char *cells_name = "#pinctrl-cells";
	int cells_size, error;

	error = of_property_read_u32(np->parent, cells_name, &cells_size);
	if (error) {
		error = of_property_read_u32(np->parent->parent,
					     cells_name, &cells_size);
		if (error)
			return -ENOENT;
	}

	return cells_size;
}