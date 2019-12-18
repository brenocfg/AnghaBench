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
struct TYPE_2__ {scalar_t__ blank_nvm_mode; } ;
struct ice_hw {TYPE_1__ nvm; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_aq_res_access_type { ____Placeholder_ice_aq_res_access_type } ice_aq_res_access_type ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_NVM_RES_ID ; 
 int /*<<< orphan*/  ICE_NVM_TIMEOUT ; 
 int ice_acquire_res (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_acquire_nvm(struct ice_hw *hw, enum ice_aq_res_access_type access)
{
	if (hw->nvm.blank_nvm_mode)
		return 0;

	return ice_acquire_res(hw, ICE_NVM_RES_ID, access, ICE_NVM_TIMEOUT);
}