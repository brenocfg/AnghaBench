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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 void const* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* property_get_pointer (struct property_entry const*) ; 
 struct property_entry* pset_prop_get (struct property_set const*,char const*) ; 

__attribute__((used)) static const void *pset_prop_find(const struct property_set *pset,
				  const char *propname, size_t length)
{
	const struct property_entry *prop;
	const void *pointer;

	prop = pset_prop_get(pset, propname);
	if (!prop)
		return ERR_PTR(-EINVAL);
	pointer = property_get_pointer(prop);
	if (!pointer)
		return ERR_PTR(-ENODATA);
	if (length > prop->length)
		return ERR_PTR(-EOVERFLOW);
	return pointer;
}