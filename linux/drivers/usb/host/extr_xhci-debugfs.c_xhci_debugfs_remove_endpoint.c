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
struct xhci_slot_priv {struct xhci_ep_priv** eps; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_priv {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_ep_priv*) ; 

void xhci_debugfs_remove_endpoint(struct xhci_hcd *xhci,
				  struct xhci_virt_device *dev,
				  int ep_index)
{
	struct xhci_ep_priv	*epriv;
	struct xhci_slot_priv	*spriv = dev->debugfs_private;

	if (!spriv || !spriv->eps[ep_index])
		return;

	epriv = spriv->eps[ep_index];
	debugfs_remove_recursive(epriv->root);
	spriv->eps[ep_index] = NULL;
	kfree(epriv);
}