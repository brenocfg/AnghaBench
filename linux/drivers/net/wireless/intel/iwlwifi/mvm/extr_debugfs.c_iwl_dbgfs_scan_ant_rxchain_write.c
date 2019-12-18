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
typedef  int u8 ;
struct iwl_mvm {int scan_rx_ant; TYPE_1__* fw; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int ANT_ABC ; 
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_config_scan (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_get_valid_rx_ant (struct iwl_mvm*) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static ssize_t
iwl_dbgfs_scan_ant_rxchain_write(struct iwl_mvm *mvm, char *buf,
				 size_t count, loff_t *ppos)
{
	u8 scan_rx_ant;

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	if (sscanf(buf, "%hhx", &scan_rx_ant) != 1)
		return -EINVAL;
	if (scan_rx_ant > ANT_ABC)
		return -EINVAL;
	if (scan_rx_ant & ~(iwl_mvm_get_valid_rx_ant(mvm)))
		return -EINVAL;

	if (mvm->scan_rx_ant != scan_rx_ant) {
		mvm->scan_rx_ant = scan_rx_ant;
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_UMAC_SCAN))
			iwl_mvm_config_scan(mvm);
	}

	return count;
}