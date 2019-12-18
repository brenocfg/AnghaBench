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
struct uart_port {int flags; int /*<<< orphan*/ * membase; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UPF_IOREMAP ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lqasc_release_port(struct uart_port *port)
{
	struct platform_device *pdev = to_platform_device(port->dev);

	if (port->flags & UPF_IOREMAP) {
		devm_iounmap(&pdev->dev, port->membase);
		port->membase = NULL;
	}
}