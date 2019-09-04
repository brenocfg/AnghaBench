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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  portnum; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_STATE ; 
 int /*<<< orphan*/  QLC_DEV_CLR_RST_QSCNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_clr_drv_state(struct qlcnic_adapter *adapter)
{
	u32  val;

	if (qlcnic_api_lock(adapter))
		return -EBUSY;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);

	return 0;
}