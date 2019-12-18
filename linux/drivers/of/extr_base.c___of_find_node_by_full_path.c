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
 struct device_node* __of_find_node_by_path (struct device_node*,char const*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 char* strchr (char const*,char) ; 
 char* strchrnul (char const*,char) ; 

struct device_node *__of_find_node_by_full_path(struct device_node *node,
						const char *path)
{
	const char *separator = strchr(path, ':');

	while (node && *path == '/') {
		struct device_node *tmp = node;

		path++; /* Increment past '/' delimiter */
		node = __of_find_node_by_path(node, path);
		of_node_put(tmp);
		path = strchrnul(path, '/');
		if (separator && separator < path)
			break;
	}
	return node;
}