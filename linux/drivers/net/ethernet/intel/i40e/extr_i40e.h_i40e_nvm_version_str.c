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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int oem_ver; scalar_t__ eetrack; int version; } ;
struct i40e_hw {TYPE_1__ nvm; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int I40E_NVM_VERSION_HI_MASK ; 
 int I40E_NVM_VERSION_HI_SHIFT ; 
 int I40E_NVM_VERSION_LO_MASK ; 
 int I40E_NVM_VERSION_LO_SHIFT ; 
 scalar_t__ I40E_OEM_EETRACK_ID ; 
 int I40E_OEM_GEN_SHIFT ; 
 int I40E_OEM_RELEASE_MASK ; 
 int I40E_OEM_SNAP_MASK ; 
 int I40E_OEM_SNAP_SHIFT ; 
 int I40E_OEM_VER_BUILD_MASK ; 
 int I40E_OEM_VER_BUILD_SHIFT ; 
 int I40E_OEM_VER_PATCH_MASK ; 
 int I40E_OEM_VER_SHIFT ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,scalar_t__,...) ; 

__attribute__((used)) static inline char *i40e_nvm_version_str(struct i40e_hw *hw)
{
	static char buf[32];
	u32 full_ver;

	full_ver = hw->nvm.oem_ver;

	if (hw->nvm.eetrack == I40E_OEM_EETRACK_ID) {
		u8 gen, snap;
		u16 release;

		gen = (u8)(full_ver >> I40E_OEM_GEN_SHIFT);
		snap = (u8)((full_ver & I40E_OEM_SNAP_MASK) >>
			I40E_OEM_SNAP_SHIFT);
		release = (u16)(full_ver & I40E_OEM_RELEASE_MASK);

		snprintf(buf, sizeof(buf), "%x.%x.%x", gen, snap, release);
	} else {
		u8 ver, patch;
		u16 build;

		ver = (u8)(full_ver >> I40E_OEM_VER_SHIFT);
		build = (u16)((full_ver >> I40E_OEM_VER_BUILD_SHIFT) &
			 I40E_OEM_VER_BUILD_MASK);
		patch = (u8)(full_ver & I40E_OEM_VER_PATCH_MASK);

		snprintf(buf, sizeof(buf),
			 "%x.%02x 0x%x %d.%d.%d",
			 (hw->nvm.version & I40E_NVM_VERSION_HI_MASK) >>
				I40E_NVM_VERSION_HI_SHIFT,
			 (hw->nvm.version & I40E_NVM_VERSION_LO_MASK) >>
				I40E_NVM_VERSION_LO_SHIFT,
			 hw->nvm.eetrack, ver, build, patch);
	}

	return buf;
}