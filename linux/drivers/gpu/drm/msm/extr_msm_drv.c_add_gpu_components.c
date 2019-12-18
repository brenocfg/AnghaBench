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
 int /*<<< orphan*/  compare_of ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  msm_gpu_match ; 
 scalar_t__ of_device_is_available (struct device_node*) ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int add_gpu_components(struct device *dev,
			      struct component_match **matchptr)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, msm_gpu_match);
	if (!np)
		return 0;

	if (of_device_is_available(np))
		drm_of_component_match_add(dev, matchptr, compare_of, np);

	of_node_put(np);

	return 0;
}