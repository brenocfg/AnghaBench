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
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int of_reset_control_get_count (scalar_t__) ; 
 int reset_control_get_count_from_lookup (struct device*) ; 

int reset_control_get_count(struct device *dev)
{
	if (dev->of_node)
		return of_reset_control_get_count(dev->of_node);

	return reset_control_get_count_from_lookup(dev);
}