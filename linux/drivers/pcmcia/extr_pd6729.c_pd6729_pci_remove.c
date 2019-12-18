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
struct pd6729_socket {int /*<<< orphan*/  poll_timer; int /*<<< orphan*/  socket; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  I365_CSCINT ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 int MAX_SOCKETS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pd6729_socket*) ; 
 int /*<<< orphan*/  indirect_write (struct pd6729_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int irq_mode ; 
 int /*<<< orphan*/  kfree (struct pd6729_socket*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pd6729_socket* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pd6729_pci_remove(struct pci_dev *dev)
{
	int i;
	struct pd6729_socket *socket = pci_get_drvdata(dev);

	for (i = 0; i < MAX_SOCKETS; i++) {
		/* Turn off all interrupt sources */
		indirect_write(&socket[i], I365_CSCINT, 0);
		indirect_write(&socket[i], I365_INTCTL, 0);

		pcmcia_unregister_socket(&socket[i].socket);
	}

	if (irq_mode == 1)
		free_irq(dev->irq, socket);
	else
		del_timer_sync(&socket->poll_timer);
	pci_release_regions(dev);
	pci_disable_device(dev);

	kfree(socket);
}