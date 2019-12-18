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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  enter (char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i82092aa_interrupt ; 
 int /*<<< orphan*/  leave (char*) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 int socket_count ; 
 TYPE_1__* sockets ; 

__attribute__((used)) static void i82092aa_pci_remove(struct pci_dev *dev)
{
	int i;

	enter("i82092aa_pci_remove");
	
	free_irq(dev->irq, i82092aa_interrupt);

	for (i = 0; i < socket_count; i++)
		pcmcia_unregister_socket(&sockets[i].socket);

	leave("i82092aa_pci_remove");
}