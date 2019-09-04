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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ sr_words; } ;
struct ice_hw {TYPE_1__ nvm; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_NVM ; 
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_SR_SECTOR_SIZE_IN_WORDS ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum ice_status
ice_check_sr_access_params(struct ice_hw *hw, u32 offset, u16 words)
{
	if ((offset + words) > hw->nvm.sr_words) {
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM error: offset beyond SR lmt.\n");
		return ICE_ERR_PARAM;
	}

	if (words > ICE_SR_SECTOR_SIZE_IN_WORDS) {
		/* We can access only up to 4KB (one sector), in one AQ write */
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM error: tried to access %d words, limit is %d.\n",
			  words, ICE_SR_SECTOR_SIZE_IN_WORDS);
		return ICE_ERR_PARAM;
	}

	if (((offset + (words - 1)) / ICE_SR_SECTOR_SIZE_IN_WORDS) !=
	    (offset / ICE_SR_SECTOR_SIZE_IN_WORDS)) {
		/* A single access cannot spread over two sectors */
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM error: cannot spread over two sectors.\n");
		return ICE_ERR_PARAM;
	}

	return 0;
}