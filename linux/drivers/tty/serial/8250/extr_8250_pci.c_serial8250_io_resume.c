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
struct serial_private {int /*<<< orphan*/  board; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct serial_private*) ; 
 int /*<<< orphan*/  kfree (struct serial_private*) ; 
 struct serial_private* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct serial_private*) ; 
 struct serial_private* pciserial_init_ports (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial8250_io_resume(struct pci_dev *dev)
{
	struct serial_private *priv = pci_get_drvdata(dev);
	struct serial_private *new;

	if (!priv)
		return;

	new = pciserial_init_ports(dev, priv->board);
	if (!IS_ERR(new)) {
		pci_set_drvdata(dev, new);
		kfree(priv);
	}
}