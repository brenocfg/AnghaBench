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
struct qlcnic_dcb_mbx_params {int /*<<< orphan*/  prio_tc_map; int /*<<< orphan*/ * type; } ;
struct qlcnic_dcb {int /*<<< orphan*/  adapter; struct qlcnic_dcb_mbx_params* param; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_82XX_DCB_PRIO_TC_MAP ; 
 int /*<<< orphan*/  QLC_DCB_LOCAL_PARAM_FWID ; 
 int /*<<< orphan*/  QLC_DCB_OPER_PARAM_FWID ; 
 int /*<<< orphan*/  QLC_DCB_PEER_PARAM_FWID ; 
 int /*<<< orphan*/  qlcnic_dcb_data_cee_param_map (int /*<<< orphan*/ ) ; 
 int qlcnic_dcb_query_cee_param (struct qlcnic_dcb*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_82xx_dcb_get_cee_cfg(struct qlcnic_dcb *dcb)
{
	struct qlcnic_dcb_mbx_params *mbx;
	int err;

	mbx = dcb->param;
	if (!mbx)
		return 0;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[0],
					 QLC_DCB_LOCAL_PARAM_FWID);
	if (err)
		return err;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[1],
					 QLC_DCB_OPER_PARAM_FWID);
	if (err)
		return err;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[2],
					 QLC_DCB_PEER_PARAM_FWID);
	if (err)
		return err;

	mbx->prio_tc_map = QLC_82XX_DCB_PRIO_TC_MAP;

	qlcnic_dcb_data_cee_param_map(dcb->adapter);

	return err;
}