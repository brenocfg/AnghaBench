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
struct property {struct property* value; struct property* name; struct property* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct property*) ; 

__attribute__((used)) static void property_list_free(struct property *prop_list)
{
	struct property *prop, *next;

	for (prop = prop_list; prop != NULL; prop = next) {
		next = prop->next;
		kfree(prop->name);
		kfree(prop->value);
		kfree(prop);
	}
}