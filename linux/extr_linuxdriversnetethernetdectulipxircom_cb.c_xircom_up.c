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
struct xircom_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NUMDESCRIPTORS ; 
 int /*<<< orphan*/  PCI_POWERMGMT ; 
 int /*<<< orphan*/ * bufferoffsets ; 
 int /*<<< orphan*/  enable_common_interrupts (struct xircom_private*) ; 
 int /*<<< orphan*/  enable_link_interrupt (struct xircom_private*) ; 
 int /*<<< orphan*/  enable_promisc (struct xircom_private*) ; 
 int /*<<< orphan*/  enable_receive_interrupt (struct xircom_private*) ; 
 int /*<<< orphan*/  enable_transmit_interrupt (struct xircom_private*) ; 
 int /*<<< orphan*/  investigate_read_descriptor (int /*<<< orphan*/ ,struct xircom_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_descriptors (struct xircom_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trigger_receive (struct xircom_private*) ; 
 int /*<<< orphan*/  trigger_transmit (struct xircom_private*) ; 

__attribute__((used)) static void xircom_up(struct xircom_private *card)
{
	unsigned long flags;
	int i;

	/* disable all powermanagement */
	pci_write_config_dword(card->pdev, PCI_POWERMGMT, 0x0000);

	setup_descriptors(card);

	spin_lock_irqsave(&card->lock, flags);


	enable_link_interrupt(card);
	enable_transmit_interrupt(card);
	enable_receive_interrupt(card);
	enable_common_interrupts(card);
	enable_promisc(card);

	/* The card can have received packets already, read them away now */
	for (i=0;i<NUMDESCRIPTORS;i++)
		investigate_read_descriptor(card->dev,card,i,bufferoffsets[i]);


	spin_unlock_irqrestore(&card->lock, flags);
	trigger_receive(card);
	trigger_transmit(card);
	netif_start_queue(card->dev);
}