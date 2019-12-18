#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int willing; int /*<<< orphan*/  pfccap; } ;
struct TYPE_13__ {scalar_t__ willing; } ;
struct TYPE_14__ {int willing; int* tcbwtable; int /*<<< orphan*/ * tsatable; int /*<<< orphan*/  maxtcs; } ;
struct ice_dcbx_cfg {int numapps; TYPE_4__* app; TYPE_1__ pfc; TYPE_6__ etsrec; TYPE_7__ etscfg; } ;
struct ice_port_info {struct ice_dcbx_cfg local_dcbx_cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  maxtc; } ;
struct TYPE_10__ {TYPE_2__ common_cap; } ;
struct ice_hw {TYPE_3__ func_caps; struct ice_port_info* port_info; } ;
struct ice_pf {TYPE_5__* pdev; struct ice_hw hw; } ;
struct ice_aqc_port_ets_elem {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int priority; int /*<<< orphan*/  prot_id; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_APP_PROT_ID_FCOE ; 
 int /*<<< orphan*/  ICE_APP_SEL_ETHTYPE ; 
 int /*<<< orphan*/  ICE_IEEE_TSA_ETS ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_dcbx_cfg*) ; 
 struct ice_dcbx_cfg* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_pf_dcb_cfg (struct ice_pf*,struct ice_dcbx_cfg*,int) ; 
 int ice_query_port_ets (struct ice_port_info*,struct ice_aqc_port_ets_elem*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memset (struct ice_dcbx_cfg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_dcb_sw_dflt_cfg(struct ice_pf *pf, bool locked)
{
	struct ice_aqc_port_ets_elem buf = { 0 };
	struct ice_dcbx_cfg *dcbcfg;
	struct ice_port_info *pi;
	struct ice_hw *hw;
	int ret;

	hw = &pf->hw;
	pi = hw->port_info;
	dcbcfg = devm_kzalloc(&pf->pdev->dev, sizeof(*dcbcfg), GFP_KERNEL);

	memset(dcbcfg, 0, sizeof(*dcbcfg));
	memset(&pi->local_dcbx_cfg, 0, sizeof(*dcbcfg));

	dcbcfg->etscfg.willing = 1;
	dcbcfg->etscfg.maxtcs = hw->func_caps.common_cap.maxtc;
	dcbcfg->etscfg.tcbwtable[0] = 100;
	dcbcfg->etscfg.tsatable[0] = ICE_IEEE_TSA_ETS;

	memcpy(&dcbcfg->etsrec, &dcbcfg->etscfg,
	       sizeof(dcbcfg->etsrec));
	dcbcfg->etsrec.willing = 0;

	dcbcfg->pfc.willing = 1;
	dcbcfg->pfc.pfccap = hw->func_caps.common_cap.maxtc;

	dcbcfg->numapps = 1;
	dcbcfg->app[0].selector = ICE_APP_SEL_ETHTYPE;
	dcbcfg->app[0].priority = 3;
	dcbcfg->app[0].prot_id = ICE_APP_PROT_ID_FCOE;

	ret = ice_pf_dcb_cfg(pf, dcbcfg, locked);
	devm_kfree(&pf->pdev->dev, dcbcfg);
	if (ret)
		return ret;

	return ice_query_port_ets(pi, &buf, sizeof(buf), NULL);
}