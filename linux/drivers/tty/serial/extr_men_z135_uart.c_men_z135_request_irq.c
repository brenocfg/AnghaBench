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
struct uart_port {int /*<<< orphan*/  irq; } ;
struct men_z135_port {struct uart_port port; TYPE_1__* mdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  men_z135_intr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct men_z135_port*) ; 

__attribute__((used)) static int men_z135_request_irq(struct men_z135_port *uart)
{
	struct device *dev = &uart->mdev->dev;
	struct uart_port *port = &uart->port;
	int err = 0;

	err = request_irq(port->irq, men_z135_intr, IRQF_SHARED,
			"men_z135_intr", uart);
	if (err)
		dev_err(dev, "Error %d getting interrupt\n", err);

	return err;
}