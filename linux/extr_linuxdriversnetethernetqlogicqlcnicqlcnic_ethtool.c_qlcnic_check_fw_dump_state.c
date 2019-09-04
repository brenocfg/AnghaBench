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
typedef  int u32 ;
struct qlcnic_fw_dump {int enable; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_fw_dump fw_dump; } ;

/* Variables and functions */
 int QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_IDC_CTRL ; 
 int QLC_83XX_IDC_DISABLE_FW_DUMP ; 
 scalar_t__ qlcnic_84xx_check (struct qlcnic_adapter*) ; 

bool qlcnic_check_fw_dump_state(struct qlcnic_adapter *adapter)
{
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	bool state;
	u32 val;

	if (qlcnic_84xx_check(adapter)) {
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		state = (val & QLC_83XX_IDC_DISABLE_FW_DUMP) ? false : true;
	} else {
		state = fw_dump->enable;
	}

	return state;
}