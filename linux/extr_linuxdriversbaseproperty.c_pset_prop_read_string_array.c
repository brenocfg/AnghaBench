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
struct property_entry {int /*<<< orphan*/  is_array; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void const*) ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  memcpy (char const**,void const*,size_t) ; 
 size_t min (size_t,size_t) ; 
 size_t pset_prop_count_elems_of_size (struct property_set const*,char const*,int) ; 
 void* pset_prop_find (struct property_set const*,char const*,size_t) ; 
 struct property_entry* pset_prop_get (struct property_set const*,char const*) ; 

__attribute__((used)) static int pset_prop_read_string_array(const struct property_set *pset,
				       const char *propname,
				       const char **strings, size_t nval)
{
	const struct property_entry *prop;
	const void *pointer;
	size_t array_len, length;

	/* Find out the array length. */
	prop = pset_prop_get(pset, propname);
	if (!prop)
		return -EINVAL;

	if (!prop->is_array)
		/* The array length for a non-array string property is 1. */
		array_len = 1;
	else
		/* Find the length of an array. */
		array_len = pset_prop_count_elems_of_size(pset, propname,
							  sizeof(const char *));

	/* Return how many there are if strings is NULL. */
	if (!strings)
		return array_len;

	array_len = min(nval, array_len);
	length = array_len * sizeof(*strings);

	pointer = pset_prop_find(pset, propname, length);
	if (IS_ERR(pointer))
		return PTR_ERR(pointer);

	memcpy(strings, pointer, length);

	return array_len;
}