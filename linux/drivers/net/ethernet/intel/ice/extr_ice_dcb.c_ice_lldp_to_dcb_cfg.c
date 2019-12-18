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
typedef  int u16 ;
typedef  int /*<<< orphan*/  typelen ;
struct ice_lldp_org_tlv {int /*<<< orphan*/  typelen; } ;
struct ice_dcbx_cfg {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int ICE_ERR_PARAM ; 
 int ICE_LLDPDU_SIZE ; 
 int ICE_LLDP_TLV_LEN_M ; 
 int ICE_LLDP_TLV_LEN_S ; 
 int ICE_LLDP_TLV_TYPE_M ; 
 int ICE_LLDP_TLV_TYPE_S ; 
 int ICE_TLV_TYPE_END ; 
#define  ICE_TLV_TYPE_ORG 128 
 int /*<<< orphan*/  ice_parse_org_tlv (struct ice_lldp_org_tlv*,struct ice_dcbx_cfg*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_lldp_to_dcb_cfg(u8 *lldpmib, struct ice_dcbx_cfg *dcbcfg)
{
	struct ice_lldp_org_tlv *tlv;
	enum ice_status ret = 0;
	u16 offset = 0;
	u16 typelen;
	u16 type;
	u16 len;

	if (!lldpmib || !dcbcfg)
		return ICE_ERR_PARAM;

	/* set to the start of LLDPDU */
	lldpmib += ETH_HLEN;
	tlv = (struct ice_lldp_org_tlv *)lldpmib;
	while (1) {
		typelen = ntohs(tlv->typelen);
		type = ((typelen & ICE_LLDP_TLV_TYPE_M) >> ICE_LLDP_TLV_TYPE_S);
		len = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);
		offset += sizeof(typelen) + len;

		/* END TLV or beyond LLDPDU size */
		if (type == ICE_TLV_TYPE_END || offset > ICE_LLDPDU_SIZE)
			break;

		switch (type) {
		case ICE_TLV_TYPE_ORG:
			ice_parse_org_tlv(tlv, dcbcfg);
			break;
		default:
			break;
		}

		/* Move to next TLV */
		tlv = (struct ice_lldp_org_tlv *)
		      ((char *)tlv + sizeof(tlv->typelen) + len);
	}

	return ret;
}