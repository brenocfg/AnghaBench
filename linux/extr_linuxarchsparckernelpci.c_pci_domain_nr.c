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
struct pci_pbm_info {int index; } ;
struct pci_bus {struct pci_pbm_info* sysdata; } ;

/* Variables and functions */
 int ENXIO ; 

int pci_domain_nr(struct pci_bus *pbus)
{
	struct pci_pbm_info *pbm = pbus->sysdata;
	int ret;

	if (!pbm) {
		ret = -ENXIO;
	} else {
		ret = pbm->index;
	}

	return ret;
}