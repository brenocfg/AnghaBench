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
struct smi_port {scalar_t__ enable; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_port_disableInterrupt (struct smi_port*) ; 
 int /*<<< orphan*/  smi_port_dma_free (struct smi_port*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smi_port_exit(struct smi_port *port)
{
	smi_port_disableInterrupt(port);
	tasklet_kill(&port->tasklet);
	smi_port_dma_free(port);
	port->enable = 0;
}