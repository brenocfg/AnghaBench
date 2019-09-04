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
typedef  void* u8 ;
struct TYPE_2__ {int willing; void* pfccap; void* pfcenable; } ;
struct i40e_dcbx_config {TYPE_1__ pfc; } ;
struct i40e_cee_feat_tlv {void** tlvinfo; int en_will_err; } ;

/* Variables and functions */
 int I40E_CEE_FEAT_TLV_WILLING_MASK ; 

__attribute__((used)) static void i40e_parse_cee_pfccfg_tlv(struct i40e_cee_feat_tlv *tlv,
				      struct i40e_dcbx_config *dcbcfg)
{
	u8 *buf = tlv->tlvinfo;

	if (tlv->en_will_err & I40E_CEE_FEAT_TLV_WILLING_MASK)
		dcbcfg->pfc.willing = 1;

	/* ------------------------
	 * | PFC Enable | PFC TCs |
	 * ------------------------
	 * | 1 octet    | 1 octet |
	 */
	dcbcfg->pfc.pfcenable = buf[0];
	dcbcfg->pfc.pfccap = buf[1];
}