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
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 char* kbasename (int /*<<< orphan*/ ) ; 
 char const* strchrnul (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

bool of_node_name_eq(const struct device_node *np, const char *name)
{
	const char *node_name;
	size_t len;

	if (!np)
		return false;

	node_name = kbasename(np->full_name);
	len = strchrnul(node_name, '@') - node_name;

	return (strlen(name) == len) && (strncmp(node_name, name, len) == 0);
}