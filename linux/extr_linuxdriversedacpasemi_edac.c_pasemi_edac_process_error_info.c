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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; TYPE_1__** csrows; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  first_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  MCDEBUG_ERRLOG1A ; 
 int MCDEBUG_ERRLOG1A_MERR_CS_M ; 
 int MCDEBUG_ERRLOG1A_MERR_CS_S ; 
 int MCDEBUG_ERRSTA_MBE_STATUS ; 
 int MCDEBUG_ERRSTA_RFL_STATUS ; 
 int MCDEBUG_ERRSTA_SBE_STATUS ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pasemi_edac_process_error_info(struct mem_ctl_info *mci, u32 errsta)
{
	struct pci_dev *pdev = to_pci_dev(mci->pdev);
	u32 errlog1a;
	u32 cs;

	if (!errsta)
		return;

	pci_read_config_dword(pdev, MCDEBUG_ERRLOG1A, &errlog1a);

	cs = (errlog1a & MCDEBUG_ERRLOG1A_MERR_CS_M) >>
		MCDEBUG_ERRLOG1A_MERR_CS_S;

	/* uncorrectable/multi-bit errors */
	if (errsta & (MCDEBUG_ERRSTA_MBE_STATUS |
		      MCDEBUG_ERRSTA_RFL_STATUS)) {
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     mci->csrows[cs]->first_page, 0, 0,
				     cs, 0, -1, mci->ctl_name, "");
	}

	/* correctable/single-bit errors */
	if (errsta & MCDEBUG_ERRSTA_SBE_STATUS)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     mci->csrows[cs]->first_page, 0, 0,
				     cs, 0, -1, mci->ctl_name, "");
}