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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ice_lldp_org_tlv {int /*<<< orphan*/  ouisubtype; int /*<<< orphan*/  typelen; int /*<<< orphan*/ * tlvinfo; } ;
struct ice_dcb_ets_cfg {int dummy; } ;
struct ice_dcbx_cfg {struct ice_dcb_ets_cfg etsrec; } ;

/* Variables and functions */
 int ICE_IEEE_8021QAZ_OUI ; 
 int ICE_IEEE_ETS_TLV_LEN ; 
 int ICE_IEEE_SUBTYPE_ETS_REC ; 
 int ICE_LLDP_TLV_OUI_S ; 
 int ICE_LLDP_TLV_TYPE_S ; 
 int ICE_TLV_TYPE_ORG ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ice_add_ieee_ets_common_tlv (int /*<<< orphan*/ *,struct ice_dcb_ets_cfg*) ; 

__attribute__((used)) static void
ice_add_ieee_etsrec_tlv(struct ice_lldp_org_tlv *tlv,
			struct ice_dcbx_cfg *dcbcfg)
{
	struct ice_dcb_ets_cfg *etsrec;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;
	u16 typelen;

	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) |
		   ICE_IEEE_ETS_TLV_LEN);
	tlv->typelen = htons(typelen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_REC);
	tlv->ouisubtype = htonl(ouisubtype);

	etsrec = &dcbcfg->etsrec;

	/* First Octet is reserved */
	/* Begin adding at Priority Assignment Table (offset 1 in buf) */
	ice_add_ieee_ets_common_tlv(&buf[1], etsrec);
}