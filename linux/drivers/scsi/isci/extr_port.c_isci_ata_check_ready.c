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
struct isci_remote_device {int dummy; } ;
struct isci_port {int /*<<< orphan*/  active_phy_mask; int /*<<< orphan*/  state; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; } ;
struct domain_device {TYPE_1__* port; } ;
struct TYPE_2__ {struct isci_port* lldd_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPORT_RESET_PENDING ; 
 struct isci_host* dev_to_ihost (struct domain_device*) ; 
 struct isci_remote_device* isci_lookup_device (struct domain_device*) ; 
 int /*<<< orphan*/  isci_put_device (struct isci_remote_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int isci_ata_check_ready(struct domain_device *dev)
{
	struct isci_port *iport = dev->port->lldd_port;
	struct isci_host *ihost = dev_to_ihost(dev);
	struct isci_remote_device *idev;
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_lookup_device(dev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	if (!idev)
		goto out;

	if (test_bit(IPORT_RESET_PENDING, &iport->state))
		goto out;

	rc = !!iport->active_phy_mask;
 out:
	isci_put_device(idev);

	return rc;
}