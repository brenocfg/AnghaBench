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
typedef  int u8 ;
typedef  int u16 ;
struct i40e_pf {int mac_seid; int lan_veb; int pf_seid; int main_vsi_seid; TYPE_2__* pdev; TYPE_1__** veb; } ;
struct i40e_aqc_switch_config_element_resp {int element_type; int /*<<< orphan*/  seid; int /*<<< orphan*/  uplink_seid; int /*<<< orphan*/  downlink_seid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int seid; int uplink_seid; int /*<<< orphan*/  veb_idx; struct i40e_pf* pf; } ;

/* Variables and functions */
 int I40E_MAX_VEB ; 
 int /*<<< orphan*/  I40E_NO_VEB ; 
#define  I40E_SWITCH_ELEMENT_TYPE_BMC 136 
#define  I40E_SWITCH_ELEMENT_TYPE_EMP 135 
#define  I40E_SWITCH_ELEMENT_TYPE_MAC 134 
#define  I40E_SWITCH_ELEMENT_TYPE_PA 133 
#define  I40E_SWITCH_ELEMENT_TYPE_PE 132 
#define  I40E_SWITCH_ELEMENT_TYPE_PF 131 
#define  I40E_SWITCH_ELEMENT_TYPE_VEB 130 
#define  I40E_SWITCH_ELEMENT_TYPE_VF 129 
#define  I40E_SWITCH_ELEMENT_TYPE_VSI 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int i40e_veb_mem_alloc (struct i40e_pf*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_setup_pf_switch_element(struct i40e_pf *pf,
				struct i40e_aqc_switch_config_element_resp *ele,
				u16 num_reported, bool printconfig)
{
	u16 downlink_seid = le16_to_cpu(ele->downlink_seid);
	u16 uplink_seid = le16_to_cpu(ele->uplink_seid);
	u8 element_type = ele->element_type;
	u16 seid = le16_to_cpu(ele->seid);

	if (printconfig)
		dev_info(&pf->pdev->dev,
			 "type=%d seid=%d uplink=%d downlink=%d\n",
			 element_type, seid, uplink_seid, downlink_seid);

	switch (element_type) {
	case I40E_SWITCH_ELEMENT_TYPE_MAC:
		pf->mac_seid = seid;
		break;
	case I40E_SWITCH_ELEMENT_TYPE_VEB:
		/* Main VEB? */
		if (uplink_seid != pf->mac_seid)
			break;
		if (pf->lan_veb >= I40E_MAX_VEB) {
			int v;

			/* find existing or else empty VEB */
			for (v = 0; v < I40E_MAX_VEB; v++) {
				if (pf->veb[v] && (pf->veb[v]->seid == seid)) {
					pf->lan_veb = v;
					break;
				}
			}
			if (pf->lan_veb >= I40E_MAX_VEB) {
				v = i40e_veb_mem_alloc(pf);
				if (v < 0)
					break;
				pf->lan_veb = v;
			}
		}
		if (pf->lan_veb >= I40E_MAX_VEB)
			break;

		pf->veb[pf->lan_veb]->seid = seid;
		pf->veb[pf->lan_veb]->uplink_seid = pf->mac_seid;
		pf->veb[pf->lan_veb]->pf = pf;
		pf->veb[pf->lan_veb]->veb_idx = I40E_NO_VEB;
		break;
	case I40E_SWITCH_ELEMENT_TYPE_VSI:
		if (num_reported != 1)
			break;
		/* This is immediately after a reset so we can assume this is
		 * the PF's VSI
		 */
		pf->mac_seid = uplink_seid;
		pf->pf_seid = downlink_seid;
		pf->main_vsi_seid = seid;
		if (printconfig)
			dev_info(&pf->pdev->dev,
				 "pf_seid=%d main_vsi_seid=%d\n",
				 pf->pf_seid, pf->main_vsi_seid);
		break;
	case I40E_SWITCH_ELEMENT_TYPE_PF:
	case I40E_SWITCH_ELEMENT_TYPE_VF:
	case I40E_SWITCH_ELEMENT_TYPE_EMP:
	case I40E_SWITCH_ELEMENT_TYPE_BMC:
	case I40E_SWITCH_ELEMENT_TYPE_PE:
	case I40E_SWITCH_ELEMENT_TYPE_PA:
		/* ignore these for now */
		break;
	default:
		dev_info(&pf->pdev->dev, "unknown element type=%d seid=%d\n",
			 element_type, seid);
		break;
	}
}