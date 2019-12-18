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
struct pci_dev {int devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static unsigned long map_types_idx(struct pci_dev *client)
{
	return (pci_domain_nr(client->bus) << 16) |
		(client->bus->number << 8) | client->devfn;
}