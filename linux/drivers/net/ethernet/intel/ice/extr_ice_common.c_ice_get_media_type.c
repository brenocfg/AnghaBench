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
struct ice_link_status {int phy_type_low; int phy_type_high; } ;
struct TYPE_2__ {struct ice_link_status link_info; } ;
struct ice_port_info {TYPE_1__ phy; } ;
typedef  enum ice_media_type { ____Placeholder_ice_media_type } ice_media_type ;

/* Variables and functions */
 int ICE_MEDIA_BACKPLANE ; 
 int ICE_MEDIA_BASET ; 
 int ICE_MEDIA_DA ; 
 int ICE_MEDIA_FIBER ; 
 int ICE_MEDIA_UNKNOWN ; 
#define  ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4 176 
#define  ICE_PHY_TYPE_LOW_1000BASE_KX 175 
#define  ICE_PHY_TYPE_LOW_1000BASE_LX 174 
#define  ICE_PHY_TYPE_LOW_1000BASE_SX 173 
#define  ICE_PHY_TYPE_LOW_1000BASE_T 172 
#define  ICE_PHY_TYPE_LOW_100BASE_TX 171 
#define  ICE_PHY_TYPE_LOW_100GBASE_CP2 170 
#define  ICE_PHY_TYPE_LOW_100GBASE_CR4 169 
#define  ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4 168 
#define  ICE_PHY_TYPE_LOW_100GBASE_DR 167 
#define  ICE_PHY_TYPE_LOW_100GBASE_KR4 166 
#define  ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4 165 
#define  ICE_PHY_TYPE_LOW_100GBASE_LR4 164 
#define  ICE_PHY_TYPE_LOW_100GBASE_SR2 163 
#define  ICE_PHY_TYPE_LOW_100GBASE_SR4 162 
#define  ICE_PHY_TYPE_LOW_10GBASE_KR_CR1 161 
#define  ICE_PHY_TYPE_LOW_10GBASE_LR 160 
#define  ICE_PHY_TYPE_LOW_10GBASE_SR 159 
#define  ICE_PHY_TYPE_LOW_10GBASE_T 158 
#define  ICE_PHY_TYPE_LOW_10G_SFI_C2C 157 
#define  ICE_PHY_TYPE_LOW_10G_SFI_DA 156 
#define  ICE_PHY_TYPE_LOW_2500BASE_KX 155 
#define  ICE_PHY_TYPE_LOW_2500BASE_T 154 
#define  ICE_PHY_TYPE_LOW_2500BASE_X 153 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR 152 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR1 151 
#define  ICE_PHY_TYPE_LOW_25GBASE_CR_S 150 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR 149 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR1 148 
#define  ICE_PHY_TYPE_LOW_25GBASE_KR_S 147 
#define  ICE_PHY_TYPE_LOW_25GBASE_LR 146 
#define  ICE_PHY_TYPE_LOW_25GBASE_SR 145 
#define  ICE_PHY_TYPE_LOW_25GBASE_T 144 
#define  ICE_PHY_TYPE_LOW_25G_AUI_C2C 143 
#define  ICE_PHY_TYPE_LOW_40GBASE_CR4 142 
#define  ICE_PHY_TYPE_LOW_40GBASE_KR4 141 
#define  ICE_PHY_TYPE_LOW_40GBASE_LR4 140 
#define  ICE_PHY_TYPE_LOW_40GBASE_SR4 139 
#define  ICE_PHY_TYPE_LOW_50GBASE_CP 138 
#define  ICE_PHY_TYPE_LOW_50GBASE_CR2 137 
#define  ICE_PHY_TYPE_LOW_50GBASE_FR 136 
#define  ICE_PHY_TYPE_LOW_50GBASE_KR2 135 
#define  ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4 134 
#define  ICE_PHY_TYPE_LOW_50GBASE_LR 133 
#define  ICE_PHY_TYPE_LOW_50GBASE_LR2 132 
#define  ICE_PHY_TYPE_LOW_50GBASE_SR 131 
#define  ICE_PHY_TYPE_LOW_50GBASE_SR2 130 
#define  ICE_PHY_TYPE_LOW_5GBASE_KR 129 
#define  ICE_PHY_TYPE_LOW_5GBASE_T 128 

__attribute__((used)) static enum ice_media_type ice_get_media_type(struct ice_port_info *pi)
{
	struct ice_link_status *hw_link_info;

	if (!pi)
		return ICE_MEDIA_UNKNOWN;

	hw_link_info = &pi->phy.link_info;
	if (hw_link_info->phy_type_low && hw_link_info->phy_type_high)
		/* If more than one media type is selected, report unknown */
		return ICE_MEDIA_UNKNOWN;

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
		case ICE_PHY_TYPE_LOW_50GBASE_SR2:
		case ICE_PHY_TYPE_LOW_50GBASE_LR2:
		case ICE_PHY_TYPE_LOW_50GBASE_SR:
		case ICE_PHY_TYPE_LOW_50GBASE_FR:
		case ICE_PHY_TYPE_LOW_50GBASE_LR:
		case ICE_PHY_TYPE_LOW_100GBASE_SR4:
		case ICE_PHY_TYPE_LOW_100GBASE_LR4:
		case ICE_PHY_TYPE_LOW_100GBASE_SR2:
		case ICE_PHY_TYPE_LOW_100GBASE_DR:
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
		case ICE_PHY_TYPE_LOW_50GBASE_CR2:
		case ICE_PHY_TYPE_LOW_50GBASE_CP:
		case ICE_PHY_TYPE_LOW_100GBASE_CR4:
		case ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4:
		case ICE_PHY_TYPE_LOW_100GBASE_CP2:
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
		case ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4:
		case ICE_PHY_TYPE_LOW_50GBASE_KR2:
		case ICE_PHY_TYPE_LOW_100GBASE_KR4:
		case ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4:
			return ICE_MEDIA_BACKPLANE;
		}
	} else {
		switch (hw_link_info->phy_type_high) {
		case ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4:
			return ICE_MEDIA_BACKPLANE;
		}
	}
	return ICE_MEDIA_UNKNOWN;
}