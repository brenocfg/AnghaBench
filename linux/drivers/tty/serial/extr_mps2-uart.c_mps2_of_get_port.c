#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int line; } ;
struct mps2_uart_port {TYPE_1__ port; int /*<<< orphan*/  flags; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPS2_MAX_PORTS ; 
 int /*<<< orphan*/  UART_PORT_COMBINED_IRQ ; 
 int idr_alloc (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  ports_idr ; 

__attribute__((used)) static int mps2_of_get_port(struct platform_device *pdev,
			    struct mps2_uart_port *mps_port)
{
	struct device_node *np = pdev->dev.of_node;
	int id;

	if (!np)
		return -ENODEV;

	id = of_alias_get_id(np, "serial");

	if (id < 0)
		id = idr_alloc_cyclic(&ports_idr, (void *)mps_port, 0, MPS2_MAX_PORTS, GFP_KERNEL);
	else
		id = idr_alloc(&ports_idr, (void *)mps_port, id, MPS2_MAX_PORTS, GFP_KERNEL);

	if (id < 0)
		return id;

	/* Only combined irq is presesnt */
	if (platform_irq_count(pdev) == 1)
		mps_port->flags |= UART_PORT_COMBINED_IRQ;

	mps_port->port.line = id;

	return 0;
}