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
struct ice_hw {int /*<<< orphan*/  intrl_gran; int /*<<< orphan*/  itr_gran; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PWR_MODE_CTL ; 
 int GL_PWR_MODE_CTL_CAR_MAX_BW_M ; 
 int GL_PWR_MODE_CTL_CAR_MAX_BW_S ; 
 int /*<<< orphan*/  ICE_INTRL_GRAN_ABOVE_25 ; 
 int /*<<< orphan*/  ICE_INTRL_GRAN_MAX_25 ; 
 int /*<<< orphan*/  ICE_ITR_GRAN_ABOVE_25 ; 
 int /*<<< orphan*/  ICE_ITR_GRAN_MAX_25 ; 
#define  ICE_MAX_AGG_BW_100G 131 
#define  ICE_MAX_AGG_BW_200G 130 
#define  ICE_MAX_AGG_BW_25G 129 
#define  ICE_MAX_AGG_BW_50G 128 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_get_itr_intrl_gran(struct ice_hw *hw)
{
	u8 max_agg_bw = (rd32(hw, GL_PWR_MODE_CTL) &
			 GL_PWR_MODE_CTL_CAR_MAX_BW_M) >>
			GL_PWR_MODE_CTL_CAR_MAX_BW_S;

	switch (max_agg_bw) {
	case ICE_MAX_AGG_BW_200G:
	case ICE_MAX_AGG_BW_100G:
	case ICE_MAX_AGG_BW_50G:
		hw->itr_gran = ICE_ITR_GRAN_ABOVE_25;
		hw->intrl_gran = ICE_INTRL_GRAN_ABOVE_25;
		break;
	case ICE_MAX_AGG_BW_25G:
		hw->itr_gran = ICE_ITR_GRAN_MAX_25;
		hw->intrl_gran = ICE_INTRL_GRAN_MAX_25;
		break;
	}
}