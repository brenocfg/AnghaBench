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
struct serial_private {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct serial_private* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pciserial_remove_ports (struct serial_private*) ; 

__attribute__((used)) static void pciserial_remove_one(struct pci_dev *dev)
{
	struct serial_private *priv = pci_get_drvdata(dev);

	pciserial_remove_ports(priv);
}