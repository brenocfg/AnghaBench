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
struct qcom_geni_serial_port {int /*<<< orphan*/  se; } ;

/* Variables and functions */
 unsigned int UART_PM_STATE_OFF ; 
 unsigned int UART_PM_STATE_ON ; 
 unsigned int UART_PM_STATE_UNDEFINED ; 
 int /*<<< orphan*/  geni_se_resources_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geni_se_resources_on (int /*<<< orphan*/ *) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 

__attribute__((used)) static void qcom_geni_serial_pm(struct uart_port *uport,
		unsigned int new_state, unsigned int old_state)
{
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	/* If we've never been called, treat it as off */
	if (old_state == UART_PM_STATE_UNDEFINED)
		old_state = UART_PM_STATE_OFF;

	if (new_state == UART_PM_STATE_ON && old_state == UART_PM_STATE_OFF)
		geni_se_resources_on(&port->se);
	else if (new_state == UART_PM_STATE_OFF &&
			old_state == UART_PM_STATE_ON)
		geni_se_resources_off(&port->se);
}