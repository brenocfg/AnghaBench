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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {int device_family; } ;

/* Variables and functions */
 int EPERM ; 
 int HPM_DEBUG ; 
#define  IWL_DEVICE_FAMILY_22000 129 
#define  IWL_DEVICE_FAMILY_9000 128 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 int PERSISTENCE_BIT ; 
 int PREG_PRPH_WPROT_22000 ; 
 int PREG_PRPH_WPROT_9000 ; 
 int PREG_WFPM_ACCESS ; 
 int iwl_read_umac_prph_no_grab (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_write_umac_prph_no_grab (struct iwl_trans*,int,int) ; 

__attribute__((used)) static int iwl_trans_pcie_clear_persistence_bit(struct iwl_trans *trans)
{
	u32 hpm, wprot;

	switch (trans->trans_cfg->device_family) {
	case IWL_DEVICE_FAMILY_9000:
		wprot = PREG_PRPH_WPROT_9000;
		break;
	case IWL_DEVICE_FAMILY_22000:
		wprot = PREG_PRPH_WPROT_22000;
		break;
	default:
		return 0;
	}

	hpm = iwl_read_umac_prph_no_grab(trans, HPM_DEBUG);
	if (hpm != 0xa5a5a5a0 && (hpm & PERSISTENCE_BIT)) {
		u32 wprot_val = iwl_read_umac_prph_no_grab(trans, wprot);

		if (wprot_val & PREG_WFPM_ACCESS) {
			IWL_ERR(trans,
				"Error, can not clear persistence bit\n");
			return -EPERM;
		}
		iwl_write_umac_prph_no_grab(trans, HPM_DEBUG,
					    hpm & ~PERSISTENCE_BIT);
	}

	return 0;
}