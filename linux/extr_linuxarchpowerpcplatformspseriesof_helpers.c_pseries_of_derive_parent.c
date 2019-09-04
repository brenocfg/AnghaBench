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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct device_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kbasename (char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

struct device_node *pseries_of_derive_parent(const char *path)
{
	struct device_node *parent;
	char *parent_path = "/";
	const char *tail;

	/* We do not want the trailing '/' character */
	tail = kbasename(path) - 1;

	/* reject if path is "/" */
	if (!strcmp(path, "/"))
		return ERR_PTR(-EINVAL);

	if (tail > path) {
		parent_path = kstrndup(path, tail - path, GFP_KERNEL);
		if (!parent_path)
			return ERR_PTR(-ENOMEM);
	}
	parent = of_find_node_by_path(parent_path);
	if (strcmp(parent_path, "/"))
		kfree(parent_path);
	return parent ? parent : ERR_PTR(-EINVAL);
}