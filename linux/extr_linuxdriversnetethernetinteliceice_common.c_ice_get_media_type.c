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
struct ice_link_status {int phy_type_low; } ;
struct TYPE_2__ {struct ice_link_status link_info; } ;
struct ice_port_info {TYPE_1__ phy; } ;
typedef  enum ice_media_type { ____Placeholder_ice_media_type } ice_media_type ;

/* Variables and functions */
 int ICE_MEDIA_BACKPLANE ; 
 int ICE_MEDIA_BASET ; 
 int ICE_MEDIA_DA ; 
 int ICE_MEDIA_FIBER ; 
 int ICE_MEDIA_UNKNOWN ; 
#define  ICE_PHY_TYPE_LOW_1000BASE_KX 157 
#define  ICE_PHY_TYPE_LOW_1000BASE_LX 156 
#define  ICE_PHY_TYPE_LOW_1000BASE_SX 155 
#define  ICE_PHY_TYPE_LOW_1000BASE_T 154 
#define  ICE_PHY_TYPE_LOW_100BASE_TX 153 
#define  ICE_PHY_TYPE_LOW_10GBASE_KR_CR1 152 
#define  ICE_PHY_TYPE_LOW_10GBASE_LR 151 
#define  ICE_PHY_TYPE_LOW_10GBASE_SR 150 
#define  ICE_PHY_TYPE_LOW_10GBASE_T 149 
#define  ICE_PHY_TYPE_LOW_10G_SFI_C2C 148 
#define  ICE_PHY_TYPE_LOW_10G_SFI_DA 147 
#define  ICE_PHY_TYPE_LOW_2500BASE_KX 146 
#define  ICE_PHY_TYPE_LOW_2500BASE_T 145 
#define  ICE_PHY_TYPE_LOW_2500BASE_X 144 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR 143 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR1 142 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR_S 141 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR 140 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR1 139 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR_S 138 
#define  ICE_PHY_TYPE_LOW_25GBASE_LR 137 
#define  ICE_PHY_TYPE_LOW_25GBASE_SR 136 
#define  ICE_PHY_TYPE_LOW_25GBASE_T 135 
#define  ICE_PHY_TYPE_LOW_25G_AUI_C2C 134 
#define  ICE_PHY_TYPE_LOW_40GBASE_CR4 133 
#define  ICE_PHY_TYPE_LOW_40GBASE_KR4 132 
#define  ICE_PHY_TYPE_LOW_40GBASE_LR4 131 
#define  ICE_PHY_TYPE_LOW_40GBASE_SR4 130 
#define  ICE_PHY_TYPE_LOW_5GBASE_KR 129 
#define  ICE_PHY_TYPE_LOW_5GBASE_T 128 

__attribute__((used)) static enum ice_media_type ice_get_media_type(struct ice_port_info *pi)
{
	struct ice_link_status *hw_link_info;

	if (!pi)
		return ICE_MEDIA_UNKNOWN;

	hw_link_info = &pi->phy.link_info;

	if (hw_link_info->phy_type_low) {
		switch (hw_link_info->phy_type_low) {
		case ICE_PHY_TYPE_LOW_1000BASE_SX:
		case ICE_PHY_TYPE_LOW_1000BASE_LX:
		case ICE_PHY_TYPE_LOW_10GBASE_SR:
		case ICE_PHY_TYPE_LOW_10GBASE_LR:
		case ICE_PHY_TYPE_LOW_10G_SFI_C2C:
		case ICE_PHY_TYPE_LOW_25GBASE_SR:
		case ICE_PHY_TYPE_LOW_25GBASE_LR:
		case ICE_PHY_TYPE_LOW_25G_AUI_C2C:
		case ICE_PHY_TYPE_LOW_40GBASE_SR4:
		case ICE_PHY_TYPE_LOW_40GBASE_LR4:
			return ICE_MEDIA_FIBER;
		case ICE_PHY_TYPE_LOW_100BASE_TX:
		case ICE_PHY_TYPE_LOW_1000BASE_T:
		case ICE_PHY_TYPE_LOW_2500BASE_T:
		case ICE_PHY_TYPE_LOW_5GBASE_T:
		case ICE_PHY_TYPE_LOW_10GBASE_T:
		case ICE_PHY_TYPE_LOW_25GBASE_T:
			return ICE_MEDIA_BASET;
		case ICE_PHY_TYPE_LOW_10G_SFI_DA:
		case ICE_PHY_TYPE_LOW_25GBASE_CR:
		case ICE_PHY_TYPE_LOW_25GBASE_CR_S:
		case ICE_PHY_TYPE_LOW_25GBASE_CR1:
		case ICE_PHY_TYPE_LOW_40GBASE_CR4:
			return ICE_MEDIA_DA;
		case ICE_PHY_TYPE_LOW_1000BASE_KX:
		case ICE_PHY_TYPE_LOW_2500BASE_KX:
		case ICE_PHY_TYPE_LOW_2500BASE_X:
		case ICE_PHY_TYPE_LOW_5GBASE_KR:
		case ICE_PHY_TYPE_LOW_10GBASE_KR_CR1:
		case ICE_PHY_TYPE_LOW_25GBASE_KR:
		case ICE_PHY_TYPE_LOW_25GBASE_KR1:
		case ICE_PHY_TYPE_LOW_25GBASE_KR_S:
		case ICE_PHY_TYPE_LOW_40GBASE_KR4:
			return ICE_MEDIA_BACKPLANE;
		}
	}

	return ICE_MEDIA_UNKNOWN;
}