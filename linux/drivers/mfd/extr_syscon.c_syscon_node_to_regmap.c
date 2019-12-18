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
struct regmap {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct regmap* device_node_get_regmap (struct device_node*,int) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 

struct regmap *syscon_node_to_regmap(struct device_node *np)
{
	if (!of_device_is_compatible(np, "syscon"))
		return ERR_PTR(-EINVAL);

	return device_node_get_regmap(np, true);
}