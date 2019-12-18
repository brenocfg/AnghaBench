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
struct property {struct property* next; } ;
struct device_node {struct property* deadprops; struct property* properties; } ;

/* Variables and functions */
 int ENODEV ; 

int __of_remove_property(struct device_node *np, struct property *prop)
{
	struct property **next;

	for (next = &np->properties; *next; next = &(*next)->next) {
		if (*next == prop)
			break;
	}
	if (*next == NULL)
		return -ENODEV;

	/* found the node */
	*next = prop->next;
	prop->next = np->deadprops;
	np->deadprops = prop;

	return 0;
}