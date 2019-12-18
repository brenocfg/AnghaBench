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
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 struct property* __of_find_property (struct device_node const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __of_node_is_type (struct device_node const*,char const*) ; 
 scalar_t__ of_compat_cmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_name_eq (struct device_node const*,char const*) ; 
 char* of_prop_next_string (struct property*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int __of_device_is_compatible(const struct device_node *device,
				     const char *compat, const char *type, const char *name)
{
	struct property *prop;
	const char *cp;
	int index = 0, score = 0;

	/* Compatible match has highest priority */
	if (compat && compat[0]) {
		prop = __of_find_property(device, "compatible", NULL);
		for (cp = of_prop_next_string(prop, NULL); cp;
		     cp = of_prop_next_string(prop, cp), index++) {
			if (of_compat_cmp(cp, compat, strlen(compat)) == 0) {
				score = INT_MAX/2 - (index << 2);
				break;
			}
		}
		if (!score)
			return 0;
	}

	/* Matching type is better than matching name */
	if (type && type[0]) {
		if (!__of_node_is_type(device, type))
			return 0;
		score += 2;
	}

	/* Matching name is a bit better than not */
	if (name && name[0]) {
		if (!of_node_name_eq(device, name))
			return 0;
		score++;
	}

	return score;
}