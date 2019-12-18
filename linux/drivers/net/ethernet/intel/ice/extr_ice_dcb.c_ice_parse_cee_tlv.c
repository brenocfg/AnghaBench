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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ice_lldp_org_tlv {int /*<<< orphan*/  typelen; int /*<<< orphan*/  ouisubtype; } ;
struct ice_dcbx_cfg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  typelen; } ;
struct ice_cee_feat_tlv {TYPE_1__ hdr; } ;
struct ice_cee_ctrl_tlv {int dummy; } ;
typedef  int /*<<< orphan*/  ouisubtype ;

/* Variables and functions */
 scalar_t__ ICE_CEE_DCBX_TYPE ; 
 scalar_t__ ICE_CEE_MAX_FEAT_TYPE ; 
#define  ICE_CEE_SUBTYPE_APP_PRI 130 
#define  ICE_CEE_SUBTYPE_PFC_CFG 129 
#define  ICE_CEE_SUBTYPE_PG_CFG 128 
 int ICE_LLDP_TLV_LEN_M ; 
 int ICE_LLDP_TLV_LEN_S ; 
 int ICE_LLDP_TLV_SUBTYPE_M ; 
 int ICE_LLDP_TLV_SUBTYPE_S ; 
 int ICE_LLDP_TLV_TYPE_M ; 
 int ICE_LLDP_TLV_TYPE_S ; 
 int /*<<< orphan*/  ice_parse_cee_app_tlv (struct ice_cee_feat_tlv*,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_parse_cee_pfccfg_tlv (struct ice_cee_feat_tlv*,struct ice_dcbx_cfg*) ; 
 int /*<<< orphan*/  ice_parse_cee_pgcfg_tlv (struct ice_cee_feat_tlv*,struct ice_dcbx_cfg*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_parse_cee_tlv(struct ice_lldp_org_tlv *tlv, struct ice_dcbx_cfg *dcbcfg)
{
	struct ice_cee_feat_tlv *sub_tlv;
	u8 subtype, feat_tlv_count = 0;
	u16 len, tlvlen, typelen;
	u32 ouisubtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & ICE_LLDP_TLV_SUBTYPE_M) >>
		       ICE_LLDP_TLV_SUBTYPE_S);
	/* Return if not CEE DCBX */
	if (subtype != ICE_CEE_DCBX_TYPE)
		return;

	typelen = ntohs(tlv->typelen);
	tlvlen = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
	len = sizeof(tlv->typelen) + sizeof(ouisubtype) +
		sizeof(struct ice_cee_ctrl_tlv);
	/* Return if no CEE DCBX Feature TLVs */
	if (tlvlen <= len)
		return;

	sub_tlv = (struct ice_cee_feat_tlv *)((char *)tlv + len);
	while (feat_tlv_count < ICE_CEE_MAX_FEAT_TYPE) {
		u16 sublen;

		typelen = ntohs(sub_tlv->hdr.typelen);
		sublen = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
		subtype = (u8)((typelen & ICE_LLDP_TLV_TYPE_M) >>
			       ICE_LLDP_TLV_TYPE_S);
		switch (subtype) {
		case ICE_CEE_SUBTYPE_PG_CFG:
			ice_parse_cee_pgcfg_tlv(sub_tlv, dcbcfg);
			break;
		case ICE_CEE_SUBTYPE_PFC_CFG:
			ice_parse_cee_pfccfg_tlv(sub_tlv, dcbcfg);
			break;
		case ICE_CEE_SUBTYPE_APP_PRI:
			ice_parse_cee_app_tlv(sub_tlv, dcbcfg);
			break;
		default:
			return;	/* Invalid Sub-type return */
		}
		feat_tlv_count++;
		/* Move to next sub TLV */
		sub_tlv = (struct ice_cee_feat_tlv *)
			  ((char *)sub_tlv + sizeof(sub_tlv->hdr.typelen) +
			   sublen);
	}
}