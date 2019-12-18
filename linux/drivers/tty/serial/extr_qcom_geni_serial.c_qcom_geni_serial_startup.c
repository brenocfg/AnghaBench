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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  line; } ;
struct qcom_geni_serial_port {int /*<<< orphan*/  name; int /*<<< orphan*/  setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  qcom_geni_serial_isr ; 
 int qcom_geni_serial_port_setup (struct uart_port*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

__attribute__((used)) static int qcom_geni_serial_startup(struct uart_port *uport)
{
	int ret;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	scnprintf(port->name, sizeof(port->name),
		  "qcom_serial_%s%d",
		(uart_console(uport) ? "console" : "uart"), uport->line);

	if (!port->setup) {
		ret = qcom_geni_serial_port_setup(uport);
		if (ret)
			return ret;
	}

	ret = request_irq(uport->irq, qcom_geni_serial_isr, IRQF_TRIGGER_HIGH,
							port->name, uport);
	if (ret)
		dev_err(uport->dev, "Failed to get IRQ ret %d\n", ret);
	return ret;
}