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
struct tasklet_struct {int dummy; } ;
struct atmel_uart_port {int /*<<< orphan*/  tasklet_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (struct tasklet_struct*) ; 

__attribute__((used)) static void atmel_tasklet_schedule(struct atmel_uart_port *atmel_port,
				   struct tasklet_struct *t)
{
	if (!atomic_read(&atmel_port->tasklet_shutdown))
		tasklet_schedule(t);
}