#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {void* of_node; TYPE_1__* parent; } ;
struct TYPE_2__ {void* of_node; } ;

/* Variables and functions */

__attribute__((used)) static int of_dev_or_parent_node_match(struct device *dev, void *data)
{
	if (dev->of_node == data)
		return 1;

	if (dev->parent)
		return dev->parent->of_node == data;

	return 0;
}