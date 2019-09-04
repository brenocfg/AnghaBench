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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_array (struct device_node*,char*,char const**,int) ; 
 char const* const* part_probe_types_def ; 

__attribute__((used)) static const char * const *of_get_probes(struct device_node *dp)
{
	const char **res;
	int count;

	count = of_property_count_strings(dp, "linux,part-probe");
	if (count < 0)
		return part_probe_types_def;

	res = kcalloc(count + 1, sizeof(*res), GFP_KERNEL);
	if (!res)
		return NULL;

	count = of_property_read_string_array(dp, "linux,part-probe", res,
					      count);
	if (count < 0)
		return NULL;

	return res;
}