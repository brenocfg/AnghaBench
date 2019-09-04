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
struct qlcnic_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_CMD_CEE_GET ; 
 int QLC_DCB_NUM_PARAM ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 int /*<<< orphan*/  dcbnl_cee_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_map_cee_params (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static void qlcnic_dcb_data_cee_param_map(struct qlcnic_adapter *adapter)
{
	int i;

	for (i = 0; i < QLC_DCB_NUM_PARAM; i++)
		qlcnic_dcb_map_cee_params(adapter, i);

	dcbnl_cee_notify(adapter->netdev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
}