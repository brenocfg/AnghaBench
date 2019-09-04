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
struct eeh_pe {int /*<<< orphan*/  data; int /*<<< orphan*/  phb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_EARLY_DUMP_LOG ; 
 int /*<<< orphan*/  eeh_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_dump_phb_diag_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnv_eeh_get_log(struct eeh_pe *pe, int severity,
			   char *drv_log, unsigned long len)
{
	if (!eeh_has_flag(EEH_EARLY_DUMP_LOG))
		pnv_pci_dump_phb_diag_data(pe->phb, pe->data);

	return 0;
}