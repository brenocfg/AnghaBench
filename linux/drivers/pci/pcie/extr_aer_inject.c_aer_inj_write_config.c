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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct aer_error {int dummy; } ;

/* Variables and functions */
 struct aer_error* __find_aer_error (int,int /*<<< orphan*/ ,unsigned int) ; 
 int aer_inj_write (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_pci_config_dword (struct aer_error*,int,int*) ; 
 int /*<<< orphan*/  inject_lock ; 
 int pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int aer_inj_write_config(struct pci_bus *bus, unsigned int devfn,
				int where, int size, u32 val)
{
	u32 *sim;
	struct aer_error *err;
	unsigned long flags;
	int rw1cs;
	int domain;
	int rv;

	spin_lock_irqsave(&inject_lock, flags);
	if (size != sizeof(u32))
		goto out;
	domain = pci_domain_nr(bus);
	if (domain < 0)
		goto out;
	err = __find_aer_error(domain, bus->number, devfn);
	if (!err)
		goto out;

	sim = find_pci_config_dword(err, where, &rw1cs);
	if (sim) {
		if (rw1cs)
			*sim ^= val;
		else
			*sim = val;
		spin_unlock_irqrestore(&inject_lock, flags);
		return 0;
	}
out:
	rv = aer_inj_write(bus, devfn, where, size, val);
	spin_unlock_irqrestore(&inject_lock, flags);
	return rv;
}