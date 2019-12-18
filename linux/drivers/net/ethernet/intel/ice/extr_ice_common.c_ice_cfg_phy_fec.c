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
struct ice_aqc_set_phy_cfg_data {int link_fec_opt; int /*<<< orphan*/  caps; } ;
typedef  enum ice_fec_mode { ____Placeholder_ice_fec_mode } ice_fec_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQC_PHY_CAPS_MASK ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ; 
 int ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ; 
 int ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN ; 
 int ICE_AQC_PHY_FEC_25G_KR_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_528_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_544_REQ ; 
 int ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN ; 
 int ICE_AQC_PHY_FEC_MASK ; 
#define  ICE_FEC_AUTO 131 
#define  ICE_FEC_BASER 130 
#define  ICE_FEC_NONE 129 
#define  ICE_FEC_RS 128 

void
ice_cfg_phy_fec(struct ice_aqc_set_phy_cfg_data *cfg, enum ice_fec_mode fec)
{
	switch (fec) {
	case ICE_FEC_BASER:
		/* Clear RS bits, and AND BASE-R ability
		 * bits and OR request bits.
		 */
		cfg->link_fec_opt &= ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN |
				     ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN;
		cfg->link_fec_opt |= ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ |
				     ICE_AQC_PHY_FEC_25G_KR_REQ;
		break;
	case ICE_FEC_RS:
		/* Clear BASE-R bits, and AND RS ability
		 * bits and OR request bits.
		 */
		cfg->link_fec_opt &= ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN;
		cfg->link_fec_opt |= ICE_AQC_PHY_FEC_25G_RS_528_REQ |
				     ICE_AQC_PHY_FEC_25G_RS_544_REQ;
		break;
	case ICE_FEC_NONE:
		/* Clear all FEC option bits. */
		cfg->link_fec_opt &= ~ICE_AQC_PHY_FEC_MASK;
		break;
	case ICE_FEC_AUTO:
		/* AND auto FEC bit, and all caps bits. */
		cfg->caps &= ICE_AQC_PHY_CAPS_MASK;
		break;
	}
}