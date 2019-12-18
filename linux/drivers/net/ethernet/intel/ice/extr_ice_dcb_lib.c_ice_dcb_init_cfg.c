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
struct ice_port_info {int /*<<< orphan*/  local_dcbx_cfg; } ;
struct TYPE_4__ {struct ice_port_info* port_info; } ;
struct ice_pf {TYPE_1__* pdev; TYPE_2__ hw; } ;
struct ice_dcbx_cfg {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_dcbx_cfg*) ; 
 struct ice_dcbx_cfg* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_pf_dcb_cfg (struct ice_pf*,struct ice_dcbx_cfg*,int) ; 
 int /*<<< orphan*/  memcpy (struct ice_dcbx_cfg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_dcb_init_cfg(struct ice_pf *pf, bool locked)
{
	struct ice_dcbx_cfg *newcfg;
	struct ice_port_info *pi;
	int ret = 0;

	pi = pf->hw.port_info;
	newcfg = devm_kzalloc(&pf->pdev->dev, sizeof(*newcfg), GFP_KERNEL);
	if (!newcfg)
		return -ENOMEM;

	memcpy(newcfg, &pi->local_dcbx_cfg, sizeof(*newcfg));
	memset(&pi->local_dcbx_cfg, 0, sizeof(*newcfg));

	dev_info(&pf->pdev->dev, "Configuring initial DCB values\n");
	if (ice_pf_dcb_cfg(pf, newcfg, locked))
		ret = -EINVAL;

	devm_kfree(&pf->pdev->dev, newcfg);

	return ret;
}