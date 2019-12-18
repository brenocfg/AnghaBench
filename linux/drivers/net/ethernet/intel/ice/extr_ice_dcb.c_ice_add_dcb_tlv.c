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
typedef  int u16 ;
struct ice_lldp_org_tlv {int dummy; } ;
struct ice_dcbx_cfg {int dummy; } ;

/* Variables and functions */
#define  ICE_IEEE_TLV_ID_APP_PRI 131 
#define  ICE_IEEE_TLV_ID_ETS_CFG 130 
#define  ICE_IEEE_TLV_ID_ETS_REC 129 
#define  ICE_IEEE_TLV_ID_PFC_CFG 128 
 int /*<<< orphan*/  ice_add_ieee_app_pri_tlv (struct ice_lldp_org_tlv*,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_add_ieee_ets_tlv (struct ice_lldp_org_tlv*,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_add_ieee_etsrec_tlv (struct ice_lldp_org_tlv*,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_add_ieee_pfc_tlv (struct ice_lldp_org_tlv*,struct ice_dcbx_cfg*) ; 

__attribute__((used)) static void
ice_add_dcb_tlv(struct ice_lldp_org_tlv *tlv, struct ice_dcbx_cfg *dcbcfg,
		u16 tlvid)
{
	switch (tlvid) {
	case ICE_IEEE_TLV_ID_ETS_CFG:
		ice_add_ieee_ets_tlv(tlv, dcbcfg);
		break;
	case ICE_IEEE_TLV_ID_ETS_REC:
		ice_add_ieee_etsrec_tlv(tlv, dcbcfg);
		break;
	case ICE_IEEE_TLV_ID_PFC_CFG:
		ice_add_ieee_pfc_tlv(tlv, dcbcfg);
		break;
	case ICE_IEEE_TLV_ID_APP_PRI:
		ice_add_ieee_app_pri_tlv(tlv, dcbcfg);
		break;
	default:
		break;
	}
}