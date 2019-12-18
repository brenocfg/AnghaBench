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
struct xhci_virt_device {TYPE_1__* eps; struct xhci_slot_priv* debugfs_private; } ;
struct xhci_slot_priv {struct xhci_ep_priv** eps; int /*<<< orphan*/  root; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_priv {int /*<<< orphan*/  name; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xhci_ep_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  xhci_debugfs_create_ring_dir (struct xhci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xhci_debugfs_create_endpoint(struct xhci_hcd *xhci,
				  struct xhci_virt_device *dev,
				  int ep_index)
{
	struct xhci_ep_priv	*epriv;
	struct xhci_slot_priv	*spriv = dev->debugfs_private;

	if (!spriv)
		return;

	if (spriv->eps[ep_index])
		return;

	epriv = kzalloc(sizeof(*epriv), GFP_KERNEL);
	if (!epriv)
		return;

	snprintf(epriv->name, sizeof(epriv->name), "ep%02d", ep_index);
	epriv->root = xhci_debugfs_create_ring_dir(xhci,
						   &dev->eps[ep_index].ring,
						   epriv->name,
						   spriv->root);
	spriv->eps[ep_index] = epriv;
}