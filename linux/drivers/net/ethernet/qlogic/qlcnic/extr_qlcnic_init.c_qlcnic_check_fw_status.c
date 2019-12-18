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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHAN_INITIALIZE_ACK ; 
 int /*<<< orphan*/  QLCNIC_CMDPEG_STATE ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_cmd_peg_ready (struct qlcnic_adapter*) ; 
 int qlcnic_receive_peg_ready (struct qlcnic_adapter*) ; 

int
qlcnic_check_fw_status(struct qlcnic_adapter *adapter)
{
	int err;

	err = qlcnic_cmd_peg_ready(adapter);
	if (err)
		return err;

	err = qlcnic_receive_peg_ready(adapter);
	if (err)
		return err;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE, PHAN_INITIALIZE_ACK);

	return err;
}