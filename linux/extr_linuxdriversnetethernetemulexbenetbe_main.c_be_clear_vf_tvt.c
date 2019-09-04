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
struct device {int dummy; } ;
struct be_vf_cfg {int privileges; int /*<<< orphan*/  if_handle; } ;
struct be_adapter {TYPE_1__* pdev; struct be_vf_cfg* vf_cfg; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int BE_PRIV_FILTMGMT ; 
 int /*<<< orphan*/  BE_RESET_VLAN_TAG_ID ; 
 int be_cmd_set_fn_privileges (struct be_adapter*,int,int) ; 
 int be_cmd_set_hsw_config (struct be_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static int be_clear_vf_tvt(struct be_adapter *adapter, int vf)
{
	struct be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	struct device *dev = &adapter->pdev->dev;
	int status;

	/* Reset Transparent VLAN Tagging. */
	status = be_cmd_set_hsw_config(adapter, BE_RESET_VLAN_TAG_ID, vf + 1,
				       vf_cfg->if_handle, 0, 0);
	if (status)
		return status;

	/* Allow VFs to program VLAN filtering */
	if (!(vf_cfg->privileges & BE_PRIV_FILTMGMT)) {
		status = be_cmd_set_fn_privileges(adapter, vf_cfg->privileges |
						  BE_PRIV_FILTMGMT, vf + 1);
		if (!status) {
			vf_cfg->privileges |= BE_PRIV_FILTMGMT;
			dev_info(dev, "VF%d: FILTMGMT priv enabled", vf);
		}
	}

	dev_info(dev,
		 "Disable/re-enable i/f in VM to clear Transparent VLAN tag");
	return 0;
}