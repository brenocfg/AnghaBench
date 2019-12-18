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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {size_t line; } ;
struct eg20t_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct eg20t_port*) ; 
 int /*<<< orphan*/  pch_uart_exit_port (struct eg20t_port*) ; 
 int /*<<< orphan*/ ** pch_uart_ports ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct eg20t_port* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void pch_uart_pci_remove(struct pci_dev *pdev)
{
	struct eg20t_port *priv = pci_get_drvdata(pdev);

	pci_disable_msi(pdev);

#ifdef CONFIG_SERIAL_PCH_UART_CONSOLE
	pch_uart_ports[priv->port.line] = NULL;
#endif
	pch_uart_exit_port(priv);
	pci_disable_device(pdev);
	kfree(priv);
	return;
}