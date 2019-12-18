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
typedef  int u32 ;
struct i40e_lldp_org_tlv {int /*<<< orphan*/  ouisubtype; } ;
struct i40e_dcbx_config {int dummy; } ;

/* Variables and functions */
#define  I40E_IEEE_SUBTYPE_APP_PRI 131 
#define  I40E_IEEE_SUBTYPE_ETS_CFG 130 
#define  I40E_IEEE_SUBTYPE_ETS_REC 129 
#define  I40E_IEEE_SUBTYPE_PFC_CFG 128 
 int I40E_LLDP_TLV_SUBTYPE_MASK ; 
 int I40E_LLDP_TLV_SUBTYPE_SHIFT ; 
 int /*<<< orphan*/  i40e_parse_ieee_app_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_ieee_etscfg_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_ieee_etsrec_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_ieee_pfccfg_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_parse_ieee_tlv(struct i40e_lldp_org_tlv *tlv,
				struct i40e_dcbx_config *dcbcfg)
{
	u32 ouisubtype;
	u8 subtype;

	ouisubtype = ntohl(tlv->ouisubtype);
	subtype = (u8)((ouisubtype & I40E_LLDP_TLV_SUBTYPE_MASK) >>
		       I40E_LLDP_TLV_SUBTYPE_SHIFT);
	switch (subtype) {
	case I40E_IEEE_SUBTYPE_ETS_CFG:
		i40e_parse_ieee_etscfg_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_SUBTYPE_ETS_REC:
		i40e_parse_ieee_etsrec_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_SUBTYPE_PFC_CFG:
		i40e_parse_ieee_pfccfg_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_SUBTYPE_APP_PRI:
		i40e_parse_ieee_app_tlv(tlv, dcbcfg);
		break;
	default:
		break;
	}
}