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
struct csio_msix_entries {int /*<<< orphan*/  desc; } ;
struct csio_hw {int num_sqsets; struct csio_msix_entries* msix_entries; } ;

/* Variables and functions */
 int CSIO_EXTRA_VECS ; 
 int CSIO_PCI_BUS (struct csio_hw*) ; 
 int CSIO_PCI_DEV (struct csio_hw*) ; 
 int CSIO_PCI_FUNC (struct csio_hw*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,...) ; 

__attribute__((used)) static void
csio_add_msix_desc(struct csio_hw *hw)
{
	int i;
	struct csio_msix_entries *entryp = &hw->msix_entries[0];
	int k = CSIO_EXTRA_VECS;
	int len = sizeof(entryp->desc) - 1;
	int cnt = hw->num_sqsets + k;

	/* Non-data vector */
	memset(entryp->desc, 0, len + 1);
	snprintf(entryp->desc, len, "csio-%02x:%02x:%x-nondata",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));

	entryp++;
	memset(entryp->desc, 0, len + 1);
	snprintf(entryp->desc, len, "csio-%02x:%02x:%x-fwevt",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));
	entryp++;

	/* Name SCSI vecs */
	for (i = k; i < cnt; i++, entryp++) {
		memset(entryp->desc, 0, len + 1);
		snprintf(entryp->desc, len, "csio-%02x:%02x:%x-scsi%d",
			 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw),
			 CSIO_PCI_FUNC(hw), i - CSIO_EXTRA_VECS);
	}
}