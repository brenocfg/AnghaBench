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
struct pci_epf_device_id {scalar_t__* name; } ;
struct pci_epf {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
pci_epf_match_id(const struct pci_epf_device_id *id, const struct pci_epf *epf)
{
	while (id->name[0]) {
		if (strcmp(epf->name, id->name) == 0)
			return true;
		id++;
	}

	return false;
}