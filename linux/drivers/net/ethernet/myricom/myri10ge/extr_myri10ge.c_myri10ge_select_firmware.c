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
typedef  int u16 ;
struct myri10ge_priv {int tx_boundary; size_t board_number; int fw_name; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MYRI10GE_MAX_BOARDS ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kernel_param_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_param_unlock (int /*<<< orphan*/ ) ; 
 char* kstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myri10ge_firmware_probe (struct myri10ge_priv*) ; 
 int myri10ge_force_firmware ; 
 char* myri10ge_fw_aligned ; 
 int /*<<< orphan*/ * myri10ge_fw_name ; 
 char** myri10ge_fw_names ; 
 char* myri10ge_fw_unaligned ; 
 int /*<<< orphan*/  pcie_capability_read_word (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_fw_name (struct myri10ge_priv*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void myri10ge_select_firmware(struct myri10ge_priv *mgp)
{
	int overridden = 0;

	if (myri10ge_force_firmware == 0) {
		int link_width;
		u16 lnk;

		pcie_capability_read_word(mgp->pdev, PCI_EXP_LNKSTA, &lnk);
		link_width = (lnk >> 4) & 0x3f;

		/* Check to see if Link is less than 8 or if the
		 * upstream bridge is known to provide aligned
		 * completions */
		if (link_width < 8) {
			dev_info(&mgp->pdev->dev, "PCIE x%d Link\n",
				 link_width);
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		} else {
			myri10ge_firmware_probe(mgp);
		}
	} else {
		if (myri10ge_force_firmware == 1) {
			dev_info(&mgp->pdev->dev,
				 "Assuming aligned completions (forced)\n");
			mgp->tx_boundary = 4096;
			set_fw_name(mgp, myri10ge_fw_aligned, false);
		} else {
			dev_info(&mgp->pdev->dev,
				 "Assuming unaligned completions (forced)\n");
			mgp->tx_boundary = 2048;
			set_fw_name(mgp, myri10ge_fw_unaligned, false);
		}
	}

	kernel_param_lock(THIS_MODULE);
	if (myri10ge_fw_name != NULL) {
		char *fw_name = kstrdup(myri10ge_fw_name, GFP_KERNEL);
		if (fw_name) {
			overridden = 1;
			set_fw_name(mgp, fw_name, true);
		}
	}
	kernel_param_unlock(THIS_MODULE);

	if (mgp->board_number < MYRI10GE_MAX_BOARDS &&
	    myri10ge_fw_names[mgp->board_number] != NULL &&
	    strlen(myri10ge_fw_names[mgp->board_number])) {
		set_fw_name(mgp, myri10ge_fw_names[mgp->board_number], false);
		overridden = 1;
	}
	if (overridden)
		dev_info(&mgp->pdev->dev, "overriding firmware to %s\n",
			 mgp->fw_name);
}