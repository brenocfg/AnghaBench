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
struct platform_device {int dummy; } ;
struct dfl_fpga_port_ops {int (* get_id ) (struct platform_device*) ;} ;

/* Variables and functions */
 struct dfl_fpga_port_ops* dfl_fpga_port_ops_get (struct platform_device*) ; 
 int /*<<< orphan*/  dfl_fpga_port_ops_put (struct dfl_fpga_port_ops*) ; 
 int stub1 (struct platform_device*) ; 

int dfl_fpga_check_port_id(struct platform_device *pdev, void *pport_id)
{
	struct dfl_fpga_port_ops *port_ops = dfl_fpga_port_ops_get(pdev);
	int port_id;

	if (!port_ops || !port_ops->get_id)
		return 0;

	port_id = port_ops->get_id(pdev);
	dfl_fpga_port_ops_put(port_ops);

	return port_id == *(int *)pport_id;
}