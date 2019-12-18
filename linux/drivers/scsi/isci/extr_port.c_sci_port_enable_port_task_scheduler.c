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
typedef  int u32 ;
struct isci_port {TYPE_1__* port_task_scheduler_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int SCU_PTSxCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUSPEND ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_port_enable_port_task_scheduler(struct isci_port *iport)
{
	u32 pts_control_value;

	 /* enable the port task scheduler in a suspended state */
	pts_control_value = readl(&iport->port_task_scheduler_registers->control);
	pts_control_value |= SCU_PTSxCR_GEN_BIT(ENABLE) | SCU_PTSxCR_GEN_BIT(SUSPEND);
	writel(pts_control_value, &iport->port_task_scheduler_registers->control);
}