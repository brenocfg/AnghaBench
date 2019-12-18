#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ num_arq_entries; scalar_t__ num_asq_entries; scalar_t__ arq_buf_size; scalar_t__ asq_buf_size; int api_maj_ver; int api_min_ver; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_min_ver; int /*<<< orphan*/  fw_maj_ver; int /*<<< orphan*/  asq_cmd_timeout; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {int version; int eetrack; int oem_ver; } ;
struct i40e_hw {int nvm_release_on_done; int /*<<< orphan*/  nvmupd_state; TYPE_3__ aq; int /*<<< orphan*/  flags; TYPE_2__ mac; TYPE_1__ nvm; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ASQ_CMD_TIMEOUT ; 
 scalar_t__ I40E_ERR_ADMIN_QUEUE_TIMEOUT ; 
 scalar_t__ I40E_ERR_CONFIG ; 
 scalar_t__ I40E_ERR_FIRMWARE_API_VERSION ; 
 int I40E_FW_API_VERSION_MAJOR ; 
 int /*<<< orphan*/  I40E_HW_FLAG_802_1AD_CAPABLE ; 
 int /*<<< orphan*/  I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE ; 
 int /*<<< orphan*/  I40E_HW_FLAG_DROP_MODE ; 
 int /*<<< orphan*/  I40E_HW_FLAG_FW_LLDP_PERSISTENT ; 
 int /*<<< orphan*/  I40E_HW_FLAG_FW_LLDP_STOPPABLE ; 
 int /*<<< orphan*/  I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK ; 
 scalar_t__ I40E_MAC_X722 ; 
 scalar_t__ I40E_MAC_XL710 ; 
 int I40E_MINOR_VER_FW_LLDP_STOPPABLE_X722 ; 
 int I40E_MINOR_VER_GET_LINK_INFO_XL710 ; 
 int /*<<< orphan*/  I40E_NVMUPD_STATE_INIT ; 
 int I40E_NVM_OEM_VER_OFF ; 
 int /*<<< orphan*/  I40E_NVM_RESOURCE_ID ; 
 int I40E_SR_BOOT_CONFIG_PTR ; 
 int I40E_SR_NVM_DEV_STARTER_VERSION ; 
 int I40E_SR_NVM_EETRACK_HI ; 
 int I40E_SR_NVM_EETRACK_LO ; 
 scalar_t__ I40E_SUCCESS ; 
 int /*<<< orphan*/  i40e_adminq_init_regs (struct i40e_hw*) ; 
 scalar_t__ i40e_aq_get_firmware_version (struct i40e_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_release_resource (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_init_arq (struct i40e_hw*) ; 
 scalar_t__ i40e_init_asq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_read_nvm_word (struct i40e_hw*,int,int*) ; 
 int /*<<< orphan*/  i40e_resume_aq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_shutdown_arq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_shutdown_asq (struct i40e_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 

i40e_status i40e_init_adminq(struct i40e_hw *hw)
{
	u16 cfg_ptr, oem_hi, oem_lo;
	u16 eetrack_lo, eetrack_hi;
	i40e_status ret_code;
	int retry = 0;

	/* verify input for valid configuration */
	if ((hw->aq.num_arq_entries == 0) ||
	    (hw->aq.num_asq_entries == 0) ||
	    (hw->aq.arq_buf_size == 0) ||
	    (hw->aq.asq_buf_size == 0)) {
		ret_code = I40E_ERR_CONFIG;
		goto init_adminq_exit;
	}

	/* Set up register offsets */
	i40e_adminq_init_regs(hw);

	/* setup ASQ command write back timeout */
	hw->aq.asq_cmd_timeout = I40E_ASQ_CMD_TIMEOUT;

	/* allocate the ASQ */
	ret_code = i40e_init_asq(hw);
	if (ret_code)
		goto init_adminq_destroy_locks;

	/* allocate the ARQ */
	ret_code = i40e_init_arq(hw);
	if (ret_code)
		goto init_adminq_free_asq;

	/* There are some cases where the firmware may not be quite ready
	 * for AdminQ operations, so we retry the AdminQ setup a few times
	 * if we see timeouts in this first AQ call.
	 */
	do {
		ret_code = i40e_aq_get_firmware_version(hw,
							&hw->aq.fw_maj_ver,
							&hw->aq.fw_min_ver,
							&hw->aq.fw_build,
							&hw->aq.api_maj_ver,
							&hw->aq.api_min_ver,
							NULL);
		if (ret_code != I40E_ERR_ADMIN_QUEUE_TIMEOUT)
			break;
		retry++;
		msleep(100);
		i40e_resume_aq(hw);
	} while (retry < 10);
	if (ret_code != I40E_SUCCESS)
		goto init_adminq_free_arq;

	/* get the NVM version info */
	i40e_read_nvm_word(hw, I40E_SR_NVM_DEV_STARTER_VERSION,
			   &hw->nvm.version);
	i40e_read_nvm_word(hw, I40E_SR_NVM_EETRACK_LO, &eetrack_lo);
	i40e_read_nvm_word(hw, I40E_SR_NVM_EETRACK_HI, &eetrack_hi);
	hw->nvm.eetrack = (eetrack_hi << 16) | eetrack_lo;
	i40e_read_nvm_word(hw, I40E_SR_BOOT_CONFIG_PTR, &cfg_ptr);
	i40e_read_nvm_word(hw, (cfg_ptr + I40E_NVM_OEM_VER_OFF),
			   &oem_hi);
	i40e_read_nvm_word(hw, (cfg_ptr + (I40E_NVM_OEM_VER_OFF + 1)),
			   &oem_lo);
	hw->nvm.oem_ver = ((u32)oem_hi << 16) | oem_lo;

	if (hw->mac.type == I40E_MAC_XL710 &&
	    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_XL710) {
		hw->flags |= I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE;
		hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;
	}
	if (hw->mac.type == I40E_MAC_X722 &&
	    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver >= I40E_MINOR_VER_FW_LLDP_STOPPABLE_X722) {
		hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;
	}

	/* Newer versions of firmware require lock when reading the NVM */
	if (hw->aq.api_maj_ver > 1 ||
	    (hw->aq.api_maj_ver == 1 &&
	     hw->aq.api_min_ver >= 5))
		hw->flags |= I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK;

	/* The ability to RX (not drop) 802.1ad frames was added in API 1.7 */
	if (hw->aq.api_maj_ver > 1 ||
	    (hw->aq.api_maj_ver == 1 &&
	     hw->aq.api_min_ver >= 7))
		hw->flags |= I40E_HW_FLAG_802_1AD_CAPABLE;

	if (hw->aq.api_maj_ver > 1 ||
	    (hw->aq.api_maj_ver == 1 &&
	     hw->aq.api_min_ver >= 8)) {
		hw->flags |= I40E_HW_FLAG_FW_LLDP_PERSISTENT;
		hw->flags |= I40E_HW_FLAG_DROP_MODE;
	}

	if (hw->aq.api_maj_ver > I40E_FW_API_VERSION_MAJOR) {
		ret_code = I40E_ERR_FIRMWARE_API_VERSION;
		goto init_adminq_free_arq;
	}

	/* pre-emptive resource lock release */
	i40e_aq_release_resource(hw, I40E_NVM_RESOURCE_ID, 0, NULL);
	hw->nvm_release_on_done = false;
	hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;

	ret_code = 0;

	/* success! */
	goto init_adminq_exit;

init_adminq_free_arq:
	i40e_shutdown_arq(hw);
init_adminq_free_asq:
	i40e_shutdown_asq(hw);
init_adminq_destroy_locks:

init_adminq_exit:
	return ret_code;
}