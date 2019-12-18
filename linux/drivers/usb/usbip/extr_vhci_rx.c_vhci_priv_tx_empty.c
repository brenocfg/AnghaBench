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
struct vhci_device {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  priv_rx; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int vhci_priv_tx_empty(struct vhci_device *vdev)
{
	int empty = 0;
	unsigned long flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);
	empty = list_empty(&vdev->priv_rx);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	return empty;
}