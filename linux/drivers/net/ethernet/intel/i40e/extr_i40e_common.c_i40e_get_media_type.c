#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int phy_type; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct i40e_hw {TYPE_2__ phy; } ;
typedef  enum i40e_media_type { ____Placeholder_i40e_media_type } i40e_media_type ;

/* Variables and functions */
 int I40E_MEDIA_TYPE_BACKPLANE ; 
 int I40E_MEDIA_TYPE_BASET ; 
 int I40E_MEDIA_TYPE_DA ; 
 int I40E_MEDIA_TYPE_FIBER ; 
 int I40E_MEDIA_TYPE_UNKNOWN ; 
#define  I40E_PHY_TYPE_1000BASE_KX 161 
#define  I40E_PHY_TYPE_1000BASE_LX 160 
#define  I40E_PHY_TYPE_1000BASE_SX 159 
#define  I40E_PHY_TYPE_1000BASE_T 158 
#define  I40E_PHY_TYPE_100BASE_TX 157 
#define  I40E_PHY_TYPE_10GBASE_AOC 156 
#define  I40E_PHY_TYPE_10GBASE_CR1 155 
#define  I40E_PHY_TYPE_10GBASE_CR1_CU 154 
#define  I40E_PHY_TYPE_10GBASE_KR 153 
#define  I40E_PHY_TYPE_10GBASE_KX4 152 
#define  I40E_PHY_TYPE_10GBASE_LR 151 
#define  I40E_PHY_TYPE_10GBASE_SFPP_CU 150 
#define  I40E_PHY_TYPE_10GBASE_SR 149 
#define  I40E_PHY_TYPE_10GBASE_T 148 
#define  I40E_PHY_TYPE_20GBASE_KR2 147 
#define  I40E_PHY_TYPE_25GBASE_ACC 146 
#define  I40E_PHY_TYPE_25GBASE_AOC 145 
#define  I40E_PHY_TYPE_25GBASE_CR 144 
#define  I40E_PHY_TYPE_25GBASE_KR 143 
#define  I40E_PHY_TYPE_25GBASE_LR 142 
#define  I40E_PHY_TYPE_25GBASE_SR 141 
#define  I40E_PHY_TYPE_2_5GBASE_T 140 
#define  I40E_PHY_TYPE_40GBASE_AOC 139 
#define  I40E_PHY_TYPE_40GBASE_CR4 138 
#define  I40E_PHY_TYPE_40GBASE_CR4_CU 137 
#define  I40E_PHY_TYPE_40GBASE_KR4 136 
#define  I40E_PHY_TYPE_40GBASE_LR4 135 
#define  I40E_PHY_TYPE_40GBASE_SR4 134 
#define  I40E_PHY_TYPE_5GBASE_T 133 
#define  I40E_PHY_TYPE_SGMII 132 
#define  I40E_PHY_TYPE_XAUI 131 
#define  I40E_PHY_TYPE_XFI 130 
#define  I40E_PHY_TYPE_XLAUI 129 
#define  I40E_PHY_TYPE_XLPPI 128 

__attribute__((used)) static enum i40e_media_type i40e_get_media_type(struct i40e_hw *hw)
{
	enum i40e_media_type media;

	switch (hw->phy.link_info.phy_type) {
	case I40E_PHY_TYPE_10GBASE_SR:
	case I40E_PHY_TYPE_10GBASE_LR:
	case I40E_PHY_TYPE_1000BASE_SX:
	case I40E_PHY_TYPE_1000BASE_LX:
	case I40E_PHY_TYPE_40GBASE_SR4:
	case I40E_PHY_TYPE_40GBASE_LR4:
	case I40E_PHY_TYPE_25GBASE_LR:
	case I40E_PHY_TYPE_25GBASE_SR:
		media = I40E_MEDIA_TYPE_FIBER;
		break;
	case I40E_PHY_TYPE_100BASE_TX:
	case I40E_PHY_TYPE_1000BASE_T:
	case I40E_PHY_TYPE_2_5GBASE_T:
	case I40E_PHY_TYPE_5GBASE_T:
	case I40E_PHY_TYPE_10GBASE_T:
		media = I40E_MEDIA_TYPE_BASET;
		break;
	case I40E_PHY_TYPE_10GBASE_CR1_CU:
	case I40E_PHY_TYPE_40GBASE_CR4_CU:
	case I40E_PHY_TYPE_10GBASE_CR1:
	case I40E_PHY_TYPE_40GBASE_CR4:
	case I40E_PHY_TYPE_10GBASE_SFPP_CU:
	case I40E_PHY_TYPE_40GBASE_AOC:
	case I40E_PHY_TYPE_10GBASE_AOC:
	case I40E_PHY_TYPE_25GBASE_CR:
	case I40E_PHY_TYPE_25GBASE_AOC:
	case I40E_PHY_TYPE_25GBASE_ACC:
		media = I40E_MEDIA_TYPE_DA;
		break;
	case I40E_PHY_TYPE_1000BASE_KX:
	case I40E_PHY_TYPE_10GBASE_KX4:
	case I40E_PHY_TYPE_10GBASE_KR:
	case I40E_PHY_TYPE_40GBASE_KR4:
	case I40E_PHY_TYPE_20GBASE_KR2:
	case I40E_PHY_TYPE_25GBASE_KR:
		media = I40E_MEDIA_TYPE_BACKPLANE;
		break;
	case I40E_PHY_TYPE_SGMII:
	case I40E_PHY_TYPE_XAUI:
	case I40E_PHY_TYPE_XFI:
	case I40E_PHY_TYPE_XLAUI:
	case I40E_PHY_TYPE_XLPPI:
	default:
		media = I40E_MEDIA_TYPE_UNKNOWN;
		break;
	}

	return media;
}