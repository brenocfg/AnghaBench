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
typedef  int u32 ;
struct i40e_lldp_org_tlv {int /*<<< orphan*/  ouisubtype; } ;
struct i40e_dcbx_config {int dummy; } ;

/* Variables and functions */
#define  I40E_CEE_DCBX_OUI 129 
#define  I40E_IEEE_8021QAZ_OUI 128 
 int I40E_LLDP_TLV_OUI_MASK ; 
 int I40E_LLDP_TLV_OUI_SHIFT ; 
 int /*<<< orphan*/  i40e_parse_cee_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_parse_ieee_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_parse_org_tlv(struct i40e_lldp_org_tlv *tlv,
			       struct i40e_dcbx_config *dcbcfg)
{
	u32 ouisubtype;
	u32 oui;

	ouisubtype = ntohl(tlv->ouisubtype);
	oui = (u32)((ouisubtype & I40E_LLDP_TLV_OUI_MASK) >>
		    I40E_LLDP_TLV_OUI_SHIFT);
	switch (oui) {
	case I40E_IEEE_8021QAZ_OUI:
		i40e_parse_ieee_tlv(tlv, dcbcfg);
		break;
	case I40E_CEE_DCBX_OUI:
		i40e_parse_cee_tlv(tlv, dcbcfg);
		break;
	default:
		break;
	}
}