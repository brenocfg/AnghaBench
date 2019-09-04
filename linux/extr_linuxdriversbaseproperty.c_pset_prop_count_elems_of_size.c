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
struct property_set {int dummy; } ;
struct property_entry {size_t length; } ;

/* Variables and functions */
 int EINVAL ; 
 struct property_entry* pset_prop_get (struct property_set const*,char const*) ; 

__attribute__((used)) static int pset_prop_count_elems_of_size(const struct property_set *pset,
					 const char *propname, size_t length)
{
	const struct property_entry *prop;

	prop = pset_prop_get(pset, propname);
	if (!prop)
		return -EINVAL;

	return prop->length / length;
}