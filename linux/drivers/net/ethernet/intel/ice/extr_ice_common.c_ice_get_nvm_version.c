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
typedef  scalar_t__ u16 ;
struct ice_nvm_info {int oem_ver; int ver; } ;
struct ice_hw {struct ice_nvm_info nvm; } ;

/* Variables and functions */
 int ICE_NVM_VER_HI_MASK ; 
 int ICE_NVM_VER_HI_SHIFT ; 
 int ICE_NVM_VER_LO_MASK ; 
 int ICE_NVM_VER_LO_SHIFT ; 
 int ICE_OEM_VER_BUILD_MASK ; 
 int ICE_OEM_VER_BUILD_SHIFT ; 
 int ICE_OEM_VER_MASK ; 
 int ICE_OEM_VER_PATCH_MASK ; 
 int ICE_OEM_VER_SHIFT ; 

void
ice_get_nvm_version(struct ice_hw *hw, u8 *oem_ver, u16 *oem_build,
		    u8 *oem_patch, u8 *ver_hi, u8 *ver_lo)
{
	struct ice_nvm_info *nvm = &hw->nvm;

	*oem_ver = (u8)((nvm->oem_ver & ICE_OEM_VER_MASK) >> ICE_OEM_VER_SHIFT);
	*oem_patch = (u8)(nvm->oem_ver & ICE_OEM_VER_PATCH_MASK);
	*oem_build = (u16)((nvm->oem_ver & ICE_OEM_VER_BUILD_MASK) >>
			   ICE_OEM_VER_BUILD_SHIFT);
	*ver_hi = (nvm->ver & ICE_NVM_VER_HI_MASK) >> ICE_NVM_VER_HI_SHIFT;
	*ver_lo = (nvm->ver & ICE_NVM_VER_LO_MASK) >> ICE_NVM_VER_LO_SHIFT;
}