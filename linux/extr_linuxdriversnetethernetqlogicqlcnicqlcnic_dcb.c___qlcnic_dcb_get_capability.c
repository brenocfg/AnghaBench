#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_dcb_capability {int tsa_capability; int ets_capability; scalar_t__ max_num_tc; scalar_t__ max_ets_tc; scalar_t__ max_pfc_tc; } ;
struct qlcnic_dcb {TYPE_3__* adapter; TYPE_1__* cfg; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct qlcnic_dcb_capability capability; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QLC_DCB_ETS_SUPPORT (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_DCB_MAX_NUM_ETS_TC (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_DCB_MAX_NUM_PFC_TC (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_DCB_MAX_NUM_TC (int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_DCB_MAX_TC ; 
 scalar_t__ QLC_DCB_TSA_SUPPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct qlcnic_dcb_capability*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_dcb_query_hw_capability (struct qlcnic_dcb*,char*) ; 

__attribute__((used)) static int __qlcnic_dcb_get_capability(struct qlcnic_dcb *dcb, u32 *val)
{
	struct qlcnic_dcb_capability *cap = &dcb->cfg->capability;
	u32 mbx_out;
	int err;

	memset(cap, 0, sizeof(struct qlcnic_dcb_capability));

	err = qlcnic_dcb_query_hw_capability(dcb, (char *)val);
	if (err)
		return err;

	mbx_out = *val;
	if (QLC_DCB_TSA_SUPPORT(mbx_out))
		cap->tsa_capability = true;

	if (QLC_DCB_ETS_SUPPORT(mbx_out))
		cap->ets_capability = true;

	cap->max_num_tc = QLC_DCB_MAX_NUM_TC(mbx_out);
	cap->max_ets_tc = QLC_DCB_MAX_NUM_ETS_TC(mbx_out);
	cap->max_pfc_tc = QLC_DCB_MAX_NUM_PFC_TC(mbx_out);

	if (cap->max_num_tc > QLC_DCB_MAX_TC ||
	    cap->max_ets_tc > cap->max_num_tc ||
	    cap->max_pfc_tc > cap->max_num_tc) {
		dev_err(&dcb->adapter->pdev->dev, "Invalid DCB configuration\n");
		return -EINVAL;
	}

	return err;
}