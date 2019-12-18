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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ice_nvm_info {int sr_words; int blank_nvm_mode; int ver; int eetrack; } ;
struct ice_hw {struct ice_nvm_info nvm; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GLNVM_FLA ; 
 int GLNVM_FLA_LOCKED_M ; 
 int /*<<< orphan*/  GLNVM_GENS ; 
 int GLNVM_GENS_SR_SIZE_M ; 
 int GLNVM_GENS_SR_SIZE_S ; 
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int /*<<< orphan*/  ICE_DBG_NVM ; 
 int ICE_ERR_NVM_BLANK_MODE ; 
 int /*<<< orphan*/  ICE_SR_NVM_DEV_STARTER_VER ; 
 int /*<<< orphan*/  ICE_SR_NVM_EETRACK_HI ; 
 int /*<<< orphan*/  ICE_SR_NVM_EETRACK_LO ; 
 int ICE_SR_WORDS_IN_1KB ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int ice_read_sr_word (struct ice_hw*,int /*<<< orphan*/ ,int*) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

enum ice_status ice_init_nvm(struct ice_hw *hw)
{
	struct ice_nvm_info *nvm = &hw->nvm;
	u16 eetrack_lo, eetrack_hi;
	enum ice_status status = 0;
	u32 fla, gens_stat;
	u8 sr_size;

	/* The SR size is stored regardless of the NVM programming mode
	 * as the blank mode may be used in the factory line.
	 */
	gens_stat = rd32(hw, GLNVM_GENS);
	sr_size = (gens_stat & GLNVM_GENS_SR_SIZE_M) >> GLNVM_GENS_SR_SIZE_S;

	/* Switching to words (sr_size contains power of 2) */
	nvm->sr_words = BIT(sr_size) * ICE_SR_WORDS_IN_1KB;

	/* Check if we are in the normal or blank NVM programming mode */
	fla = rd32(hw, GLNVM_FLA);
	if (fla & GLNVM_FLA_LOCKED_M) { /* Normal programming mode */
		nvm->blank_nvm_mode = false;
	} else { /* Blank programming mode */
		nvm->blank_nvm_mode = true;
		status = ICE_ERR_NVM_BLANK_MODE;
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM init error: unsupported blank mode.\n");
		return status;
	}

	status = ice_read_sr_word(hw, ICE_SR_NVM_DEV_STARTER_VER, &hw->nvm.ver);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Failed to read DEV starter version.\n");
		return status;
	}

	status = ice_read_sr_word(hw, ICE_SR_NVM_EETRACK_LO, &eetrack_lo);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read EETRACK lo.\n");
		return status;
	}
	status = ice_read_sr_word(hw, ICE_SR_NVM_EETRACK_HI, &eetrack_hi);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read EETRACK hi.\n");
		return status;
	}

	hw->nvm.eetrack = (eetrack_hi << 16) | eetrack_lo;

	return status;
}