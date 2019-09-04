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
struct fpga_region {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct fpga_region* fpga_region_class_find (int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_region_of_node_match ; 

__attribute__((used)) static struct fpga_region *of_fpga_region_find(struct device_node *np)
{
	return fpga_region_class_find(NULL, np, fpga_region_of_node_match);
}