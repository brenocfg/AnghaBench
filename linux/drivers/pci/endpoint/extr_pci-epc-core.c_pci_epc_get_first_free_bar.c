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
struct pci_epc_features {int /*<<< orphan*/  reserved_bar; } ;

/* Variables and functions */
 int ffz (int /*<<< orphan*/ ) ; 

unsigned int pci_epc_get_first_free_bar(const struct pci_epc_features
					*epc_features)
{
	int free_bar;

	if (!epc_features)
		return 0;

	free_bar = ffz(epc_features->reserved_bar);
	if (free_bar > 5)
		return 0;

	return free_bar;
}