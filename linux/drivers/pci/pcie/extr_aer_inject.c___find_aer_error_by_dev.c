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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct aer_error {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 struct aer_error* __find_aer_error (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static struct aer_error *__find_aer_error_by_dev(struct pci_dev *dev)
{
	int domain = pci_domain_nr(dev->bus);
	if (domain < 0)
		return NULL;
	return __find_aer_error(domain, dev->bus->number, dev->devfn);
}