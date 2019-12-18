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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sci_port {TYPE_1__ port; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 unsigned int SCI_NUM_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_port_disable(struct sci_port *sci_port)
{
	unsigned int i;

	if (!sci_port->port.dev)
		return;

	for (i = SCI_NUM_CLKS; i-- > 0; )
		clk_disable_unprepare(sci_port->clks[i]);

	pm_runtime_put_sync(sci_port->port.dev);
}