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
struct priv {int /*<<< orphan*/  pdev; int /*<<< orphan*/  rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct priv*) ; 
 int /*<<< orphan*/  pci_disable_rom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_rom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcirom_fini(void *data)
{
	struct priv *priv = data;
	pci_unmap_rom(priv->pdev, priv->rom);
	pci_disable_rom(priv->pdev);
	kfree(priv);
}