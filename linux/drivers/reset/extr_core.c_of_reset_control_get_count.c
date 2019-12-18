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
 int EINVAL ; 
 int ENOENT ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 

__attribute__((used)) static int of_reset_control_get_count(struct device_node *node)
{
	int count;

	if (!node)
		return -EINVAL;

	count = of_count_phandle_with_args(node, "resets", "#reset-cells");
	if (count == 0)
		count = -ENOENT;

	return count;
}