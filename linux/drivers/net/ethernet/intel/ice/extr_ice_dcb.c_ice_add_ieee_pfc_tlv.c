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
struct ice_lldp_org_tlv {int* tlvinfo; int /*<<< orphan*/  ouisubtype; int /*<<< orphan*/  typelen; } ;
struct TYPE_2__ {int pfccap; int pfcena; scalar_t__ mbc; scalar_t__ willing; } ;
struct ice_dcbx_cfg {TYPE_1__ pfc; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ICE_IEEE_8021QAZ_OUI ; 
 int /*<<< orphan*/  ICE_IEEE_PFC_MBC_S ; 
 int ICE_IEEE_PFC_TLV_LEN ; 
 int /*<<< orphan*/  ICE_IEEE_PFC_WILLING_S ; 
 int ICE_IEEE_SUBTYPE_PFC_CFG ; 
 int ICE_LLDP_TLV_OUI_S ; 
 int ICE_LLDP_TLV_TYPE_S ; 
 int ICE_TLV_TYPE_ORG ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
ice_add_ieee_pfc_tlv(struct ice_lldp_org_tlv *tlv, struct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;
	u16 typelen;

	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_PFC_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_PFC_CFG);
	tlv->ouisubtype = htonl(ouisubtype);

	/* ----------------------------------------
	 * |will-|MBC  | Re-  | PFC |  PFC Enable  |
	 * |ing  |     |served| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	if (dcbcfg->pfc.willing)
		buf[0] = BIT(ICE_IEEE_PFC_WILLING_S);

	if (dcbcfg->pfc.mbc)
		buf[0] |= BIT(ICE_IEEE_PFC_MBC_S);

	buf[0] |= dcbcfg->pfc.pfccap & 0xF;
	buf[1] = dcbcfg->pfc.pfcena;
}