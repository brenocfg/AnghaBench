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
struct device {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_match_add_release (struct device*,struct component_match**,int /*<<< orphan*/ ,int (*) (struct device*,void*),struct device_node*) ; 
 int /*<<< orphan*/  drm_release_of ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 

void drm_of_component_match_add(struct device *master,
				struct component_match **matchptr,
				int (*compare)(struct device *, void *),
				struct device_node *node)
{
	of_node_get(node);
	component_match_add_release(master, matchptr, drm_release_of,
				    compare, node);
}