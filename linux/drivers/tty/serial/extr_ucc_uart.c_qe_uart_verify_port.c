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
struct uart_port {int dummy; } ;
struct serial_struct {scalar_t__ type; scalar_t__ irq; int baud_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PORT_CPM ; 
 scalar_t__ PORT_UNKNOWN ; 
 scalar_t__ nr_irqs ; 

__attribute__((used)) static int qe_uart_verify_port(struct uart_port *port,
			       struct serial_struct *ser)
{
	if (ser->type != PORT_UNKNOWN && ser->type != PORT_CPM)
		return -EINVAL;

	if (ser->irq < 0 || ser->irq >= nr_irqs)
		return -EINVAL;

	if (ser->baud_base < 9600)
		return -EINVAL;

	return 0;
}