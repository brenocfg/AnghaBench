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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct ice_lldp_org_tlv {size_t* tlvinfo; int /*<<< orphan*/  typelen; int /*<<< orphan*/  ouisubtype; } ;
struct ice_dcbx_cfg {scalar_t__ numapps; TYPE_1__* app; } ;
struct TYPE_2__ {int priority; int selector; int prot_id; } ;

/* Variables and functions */
 size_t ICE_DCBX_MAX_APPS ; 
 int ICE_IEEE_8021QAZ_OUI ; 
 size_t ICE_IEEE_APP_PRIO_S ; 
 int ICE_IEEE_SUBTYPE_APP_PRI ; 
 int ICE_LLDP_TLV_OUI_S ; 
 size_t ICE_LLDP_TLV_TYPE_S ; 
 size_t ICE_TLV_TYPE_ORG ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (size_t) ; 

__attribute__((used)) static void
ice_add_ieee_app_pri_tlv(struct ice_lldp_org_tlv *tlv,
			 struct ice_dcbx_cfg *dcbcfg)
{
	u16 typelen, len, offset = 0;
	u8 priority, selector, i = 0;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	/* No APP TLVs then just return */
	if (dcbcfg->numapps == 0)
		return;
	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_LLDP_TLV_OUI_S) |
		      ICE_IEEE_SUBTYPE_APP_PRI);
	tlv->ouisubtype = htonl(ouisubtype);

	/* Move offset to App Priority Table */
	offset++;
	/* Application Priority Table (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Priority|Rsrvd| Sel |    Protocol ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	while (i < dcbcfg->numapps) {
		priority = dcbcfg->app[i].priority & 0x7;
		selector = dcbcfg->app[i].selector & 0x7;
		buf[offset] = (priority << ICE_IEEE_APP_PRIO_S) | selector;
		buf[offset + 1] = (dcbcfg->app[i].prot_id >> 0x8) & 0xFF;
		buf[offset + 2] = dcbcfg->app[i].prot_id & 0xFF;
		/* Move to next app */
		offset += 3;
		i++;
		if (i >= ICE_DCBX_MAX_APPS)
			break;
	}
	/* len includes size of ouisubtype + 1 reserved + 3*numapps */
	len = sizeof(tlv->ouisubtype) + 1 + (i * 3);
	typelen = ((ICE_TLV_TYPE_ORG << ICE_LLDP_TLV_TYPE_S) | (len & 0x1FF));
	tlv->typelen = htons(typelen);
}