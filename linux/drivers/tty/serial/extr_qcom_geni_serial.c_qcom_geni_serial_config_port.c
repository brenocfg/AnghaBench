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
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_MSM ; 
 int UART_CONFIG_TYPE ; 
 int /*<<< orphan*/  qcom_geni_serial_request_port (struct uart_port*) ; 

__attribute__((used)) static void qcom_geni_serial_config_port(struct uart_port *uport, int cfg_flags)
{
	if (cfg_flags & UART_CONFIG_TYPE) {
		uport->type = PORT_MSM;
		qcom_geni_serial_request_port(uport);
	}
}