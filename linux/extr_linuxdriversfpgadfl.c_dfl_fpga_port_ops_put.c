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
struct dfl_fpga_port_ops {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (scalar_t__) ; 

void dfl_fpga_port_ops_put(struct dfl_fpga_port_ops *ops)
{
	if (ops && ops->owner)
		module_put(ops->owner);
}