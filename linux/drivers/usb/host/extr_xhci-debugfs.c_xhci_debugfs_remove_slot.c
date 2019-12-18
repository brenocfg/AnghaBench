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
struct xhci_virt_device {struct xhci_slot_priv* debugfs_private; } ;
struct xhci_slot_priv {struct xhci_slot_priv** eps; int /*<<< orphan*/  root; } ;
struct xhci_hcd {struct xhci_virt_device** devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_slot_priv*) ; 

void xhci_debugfs_remove_slot(struct xhci_hcd *xhci, int slot_id)
{
	int			i;
	struct xhci_slot_priv	*priv;
	struct xhci_virt_device	*dev = xhci->devs[slot_id];

	if (!dev || !dev->debugfs_private)
		return;

	priv = dev->debugfs_private;

	debugfs_remove_recursive(priv->root);

	for (i = 0; i < 31; i++)
		kfree(priv->eps[i]);

	kfree(priv);
	dev->debugfs_private = NULL;
}