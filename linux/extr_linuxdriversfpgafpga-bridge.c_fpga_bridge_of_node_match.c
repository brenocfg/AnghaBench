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
struct device {void const* of_node; } ;

/* Variables and functions */

__attribute__((used)) static int fpga_bridge_of_node_match(struct device *dev, const void *data)
{
	return dev->of_node == data;
}