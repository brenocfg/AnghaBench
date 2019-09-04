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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct qlcnic_bc_trans {int /*<<< orphan*/  trans_state; TYPE_1__* vf; } ;
struct qlcnic_adapter {scalar_t__ fw_fail_cnt; int /*<<< orphan*/  ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_83XX_IDC_DEV_READY ; 
 int /*<<< orphan*/  QLC_83XX_IDC_DEV_STATE ; 
 scalar_t__ QLC_BC_CMD_MAX_RETRY_CNT ; 
 int /*<<< orphan*/  QLC_BC_VF_CHANNEL ; 
 int /*<<< orphan*/  QLC_INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int qlcnic_sriov_retry_bc_cmd(struct qlcnic_adapter *adapter,
				     struct qlcnic_bc_trans *trans)
{
	u8 max = QLC_BC_CMD_MAX_RETRY_CNT;
	u32 state;

	state = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);
	if (state == QLC_83XX_IDC_DEV_READY) {
		msleep(20);
		clear_bit(QLC_BC_VF_CHANNEL, &trans->vf->state);
		trans->trans_state = QLC_INIT;
		if (++adapter->fw_fail_cnt > max)
			return -EIO;
		else
			return 0;
	}

	return -EIO;
}