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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  portnum; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_CRB_DRV_STATE ; 
 scalar_t__ QLCNIC_DEV_NEED_QUISCENT ; 
 scalar_t__ QLCNIC_DEV_NEED_RESET ; 
 int /*<<< orphan*/  QLC_DEV_SET_QSCNT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_DEV_SET_RST_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ qlcnic_api_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_api_unlock (struct qlcnic_adapter*) ; 

__attribute__((used)) static int
qlcnic_set_drv_state(struct qlcnic_adapter *adapter, u8 state)
{
	u32  val;

	WARN_ON(state != QLCNIC_DEV_NEED_RESET &&
			state != QLCNIC_DEV_NEED_QUISCENT);

	if (qlcnic_api_lock(adapter))
		return -EIO;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);

	if (state == QLCNIC_DEV_NEED_RESET)
		QLC_DEV_SET_RST_RDY(val, adapter->portnum);
	else if (state == QLCNIC_DEV_NEED_QUISCENT)
		QLC_DEV_SET_QSCNT_RDY(val, adapter->portnum);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);

	return 0;
}