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
struct property_set {struct property_entry* properties; } ;
struct property_entry {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct property_entry *
pset_prop_get(const struct property_set *pset, const char *name)
{
	const struct property_entry *prop;

	if (!pset || !pset->properties)
		return NULL;

	for (prop = pset->properties; prop->name; prop++)
		if (!strcmp(name, prop->name))
			return prop;

	return NULL;
}