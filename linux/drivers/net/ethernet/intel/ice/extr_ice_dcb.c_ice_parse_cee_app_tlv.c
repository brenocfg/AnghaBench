#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ice_dcbx_cfg {int numapps; TYPE_2__* app; } ;
struct TYPE_3__ {int /*<<< orphan*/  typelen; } ;
struct ice_cee_feat_tlv {int tlvinfo; TYPE_1__ hdr; } ;
struct ice_cee_app_prio {int prio_map; scalar_t__ upper_oui_sel; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {void* prot_id; scalar_t__ selector; scalar_t__ priority; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 scalar_t__ ICE_APP_SEL_ETHTYPE ; 
 scalar_t__ ICE_APP_SEL_TCPIP ; 
 scalar_t__ ICE_CEE_APP_SELECTOR_M ; 
#define  ICE_CEE_APP_SEL_ETHTYPE 129 
#define  ICE_CEE_APP_SEL_TCPIP 128 
 int ICE_DCBX_MAX_APPS ; 
 int ICE_LLDP_TLV_LEN_M ; 
 int ICE_LLDP_TLV_LEN_S ; 
 scalar_t__ ICE_MAX_USER_PRIORITY ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_parse_cee_app_tlv(struct ice_cee_feat_tlv *tlv, struct ice_dcbx_cfg *dcbcfg)
{
	u16 len, typelen, offset = 0;
	struct ice_cee_app_prio *app;
	u8 i;

	typelen = ntohs(tlv->hdr.typelen);
	len = ((typelen & ICE_LLDP_TLV_LEN_M) >> ICE_LLDP_TLV_LEN_S);

	dcbcfg->numapps = len / sizeof(*app);
	if (!dcbcfg->numapps)
		return;
	if (dcbcfg->numapps > ICE_DCBX_MAX_APPS)
		dcbcfg->numapps = ICE_DCBX_MAX_APPS;

	for (i = 0; i < dcbcfg->numapps; i++) {
		u8 up, selector;

		app = (struct ice_cee_app_prio *)(tlv->tlvinfo + offset);
		for (up = 0; up < ICE_MAX_USER_PRIORITY; up++)
			if (app->prio_map & BIT(up))
				break;

		dcbcfg->app[i].priority = up;

		/* Get Selector from lower 2 bits, and convert to IEEE */
		selector = (app->upper_oui_sel & ICE_CEE_APP_SELECTOR_M);
		switch (selector) {
		case ICE_CEE_APP_SEL_ETHTYPE:
			dcbcfg->app[i].selector = ICE_APP_SEL_ETHTYPE;
			break;
		case ICE_CEE_APP_SEL_TCPIP:
			dcbcfg->app[i].selector = ICE_APP_SEL_TCPIP;
			break;
		default:
			/* Keep selector as it is for unknown types */
			dcbcfg->app[i].selector = selector;
		}

		dcbcfg->app[i].prot_id = ntohs(app->protocol);
		/* Move to next app */
		offset += sizeof(*app);
	}
}