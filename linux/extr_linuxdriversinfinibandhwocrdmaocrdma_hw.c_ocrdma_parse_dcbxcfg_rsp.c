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
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct ocrdma_dev {int /*<<< orphan*/  id; TYPE_2__ nic_info; } ;
struct ocrdma_dcbx_cfg {int tcv_aev_opv_st; int pfc_state; scalar_t__ pfc_prio; struct ocrdma_app_parameter* app_param; } ;
struct ocrdma_app_parameter {int valid_proto_app; scalar_t__ app_prio; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_P_IBOE ; 
 int OCRDMA_APP_PARAM_APP_PROTO_MASK ; 
 int OCRDMA_APP_PARAM_PROTO_SEL_MASK ; 
 int OCRDMA_APP_PARAM_PROTO_SEL_SHIFT ; 
 int OCRDMA_APP_PARAM_VALID_MASK ; 
 int OCRDMA_APP_PARAM_VALID_SHIFT ; 
 int OCRDMA_DCBX_APP_ENTRY_SHIFT ; 
 int OCRDMA_DCBX_STATE_MASK ; 
 int OCRDMA_MAX_SERVICE_LEVEL_INDEX ; 
 int OCRDMA_PROTO_SELECT_L2 ; 
 int OCRDMA_STATE_FLAG_ENABLED ; 
 int OCRDMA_STATE_FLAG_SYNC ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int ocrdma_get_app_prio (int*,int) ; 
 int ocrdma_get_pfc_prio (int*,int) ; 
 int /*<<< orphan*/  ocrdma_is_enabled_and_synced (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int ocrdma_parse_dcbxcfg_rsp(struct ocrdma_dev *dev, int ptype,
				    struct ocrdma_dcbx_cfg *dcbxcfg,
				    u8 *srvc_lvl)
{
	int status = -EINVAL, indx, slindx;
	int ventry_cnt;
	struct ocrdma_app_parameter *app_param;
	u8 valid, proto_sel;
	u8 app_prio, pfc_prio;
	u16 proto;

	if (!(dcbxcfg->tcv_aev_opv_st & OCRDMA_DCBX_STATE_MASK)) {
		pr_info("%s ocrdma%d DCBX is disabled\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
		goto out;
	}

	if (!ocrdma_is_enabled_and_synced(dcbxcfg->pfc_state)) {
		pr_info("%s ocrdma%d priority flow control(%s) is %s%s\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id,
			(ptype > 0 ? "operational" : "admin"),
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_ENABLED) ?
			"enabled" : "disabled",
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_SYNC) ?
			"" : ", not sync'ed");
		goto out;
	} else {
		pr_info("%s ocrdma%d priority flow control is enabled and sync'ed\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
	}

	ventry_cnt = (dcbxcfg->tcv_aev_opv_st >>
				OCRDMA_DCBX_APP_ENTRY_SHIFT)
				& OCRDMA_DCBX_STATE_MASK;

	for (indx = 0; indx < ventry_cnt; indx++) {
		app_param = &dcbxcfg->app_param[indx];
		valid = (app_param->valid_proto_app >>
				OCRDMA_APP_PARAM_VALID_SHIFT)
				& OCRDMA_APP_PARAM_VALID_MASK;
		proto_sel = (app_param->valid_proto_app
				>>  OCRDMA_APP_PARAM_PROTO_SEL_SHIFT)
				& OCRDMA_APP_PARAM_PROTO_SEL_MASK;
		proto = app_param->valid_proto_app &
				OCRDMA_APP_PARAM_APP_PROTO_MASK;

		if (
			valid && proto == ETH_P_IBOE &&
			proto_sel == OCRDMA_PROTO_SELECT_L2) {
			for (slindx = 0; slindx <
				OCRDMA_MAX_SERVICE_LEVEL_INDEX; slindx++) {
				app_prio = ocrdma_get_app_prio(
						(u8 *)app_param->app_prio,
						slindx);
				pfc_prio = ocrdma_get_pfc_prio(
						(u8 *)dcbxcfg->pfc_prio,
						slindx);

				if (app_prio && pfc_prio) {
					*srvc_lvl = slindx;
					status = 0;
					goto out;
				}
			}
			if (slindx == OCRDMA_MAX_SERVICE_LEVEL_INDEX) {
				pr_info("%s ocrdma%d application priority not set for 0x%x protocol\n",
					dev_name(&dev->nic_info.pdev->dev),
					dev->id, proto);
			}
		}
	}

out:
	return status;
}