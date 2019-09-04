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
struct i40e_lldp_org_tlv {int /*<<< orphan*/  typelength; int /*<<< orphan*/  ouisubtype; } ;
struct i40e_dcbx_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  typelen; } ;
struct i40e_cee_feat_tlv {TYPE_1__ hdr; } ;
struct i40e_cee_ctrl_tlv {int dummy; } ;
typedef  int /*<<< orphan*/  ouisubtype ;

/* Variables and functions */
 scalar_t__ I40E_CEE_DCBX_TYPE ; 
 scalar_t__ I40E_CEE_MAX_FEAT_TYPE ; 
#define  I40E_CEE_SUBTYPE_APP_PRI 130 
#define  I40E_CEE_SUBTYPE_PFC_CFG 129 
#define  I40E_CEE_SUBTYPE_PG_CFG 128 
 int I40E_LLDP_TLV_LEN_MASK ; 
 int I40E_LLDP_TLV_LEN_SHIFT ; 
 int I40E_LLDP_TLV_SUBTYPE_MASK ; 
 int I40E_LLDP_TLV_SUBTYPE_SHIFT ; 
 int I40E_LLDP_TLV_TYPE_MASK ; 
 int I40E_LLDP_TLV_TYPE_SHIFT ; 
 int /*<<< orphan*/  i40e_parse_cee_app_tlv (struct i40e_cee_feat_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_cee_pfccfg_tlv (struct i40e_cee_feat_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_cee_pgcfg_tlv (struct i40e_cee_feat_tlv*,struct i40e_dcbx_config*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_parse_cee_tlv(struct i40e_lldp_org_tlv *tlv,
			       struct i40e_dcbx_config *dcbcfg)
{
	u16 len, tlvlen, sublen, typelength;
	struct i40e_cee_feat_tlv *sub_tlv;
	u8 subtype, feat_tlv_count = 0;
	u32 ouisubtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & I40E_LLDP_TLV_SUBTYPE_MASK) >>
		       I40E_LLDP_TLV_SUBTYPE_SHIFT);
	/* Return if not CEE DCBX */
	if (subtype != I40E_CEE_DCBX_TYPE)
		return;

	typelength = ntohs(tlv->typelength);
	tlvlen = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
			I40E_LLDP_TLV_LEN_SHIFT);
	len = sizeof(tlv->typelength) + sizeof(ouisubtype) +
	      sizeof(struct i40e_cee_ctrl_tlv);
	/* Return if no CEE DCBX Feature TLVs */
	if (tlvlen <= len)
		return;

	sub_tlv = (struct i40e_cee_feat_tlv *)((char *)tlv + len);
	while (feat_tlv_count < I40E_CEE_MAX_FEAT_TYPE) {
		typelength = ntohs(sub_tlv->hdr.typelen);
		sublen = (u16)((typelength &
				I40E_LLDP_TLV_LEN_MASK) >>
				I40E_LLDP_TLV_LEN_SHIFT);
		subtype = (u8)((typelength & I40E_LLDP_TLV_TYPE_MASK) >>
				I40E_LLDP_TLV_TYPE_SHIFT);
		switch (subtype) {
		case I40E_CEE_SUBTYPE_PG_CFG:
			i40e_parse_cee_pgcfg_tlv(sub_tlv, dcbcfg);
			break;
		case I40E_CEE_SUBTYPE_PFC_CFG:
			i40e_parse_cee_pfccfg_tlv(sub_tlv, dcbcfg);
			break;
		case I40E_CEE_SUBTYPE_APP_PRI:
			i40e_parse_cee_app_tlv(sub_tlv, dcbcfg);
			break;
		default:
			return; /* Invalid Sub-type return */
		}
		feat_tlv_count++;
		/* Move to next sub TLV */
		sub_tlv = (struct i40e_cee_feat_tlv *)((char *)sub_tlv +
						sizeof(sub_tlv->hdr.typelen) +
						sublen);
	}
}