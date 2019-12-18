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
struct priv {int /*<<< orphan*/  bus; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcb_release_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct priv* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mcb_pci_remove(struct pci_dev *pdev)
{
	struct priv *priv = pci_get_drvdata(pdev);

	mcb_release_bus(priv->bus);

	pci_disable_device(pdev);
}