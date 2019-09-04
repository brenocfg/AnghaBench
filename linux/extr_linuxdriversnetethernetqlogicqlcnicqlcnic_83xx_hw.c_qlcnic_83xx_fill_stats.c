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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int num; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_RCODE_SUCCESS ; 
#define  QLC_83XX_STAT_MAC 130 
#define  QLC_83XX_STAT_RX 129 
#define  QLC_83XX_STAT_TX 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * qlcnic_83xx_copy_stats (struct qlcnic_cmd_args*,int /*<<< orphan*/ *,int) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static u64 *qlcnic_83xx_fill_stats(struct qlcnic_adapter *adapter,
				   struct qlcnic_cmd_args *cmd, u64 *data,
				   int type, int *ret)
{
	int err, k, total_regs;

	*ret = 0;
	err = qlcnic_issue_cmd(adapter, cmd);
	if (err != QLCNIC_RCODE_SUCCESS) {
		dev_info(&adapter->pdev->dev,
			 "Error in get statistics mailbox command\n");
		*ret = -EIO;
		return data;
	}
	total_regs = cmd->rsp.num;
	switch (type) {
	case QLC_83XX_STAT_MAC:
		/* fill in MAC tx counters */
		for (k = 2; k < 28; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 24 bytes of reserved area */
		/* fill in MAC rx counters */
		for (k += 6; k < 60; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 24 bytes of reserved area */
		/* fill in MAC rx frame stats */
		for (k += 6; k < 80; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* fill in eSwitch stats */
		for (; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		break;
	case QLC_83XX_STAT_RX:
		for (k = 2; k < 8; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes of reserved data */
		for (k += 2; k < 24; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes containing RE1FBQ error data */
		for (k += 2; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		break;
	case QLC_83XX_STAT_TX:
		for (k = 2; k < 10; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes of reserved data */
		for (k += 2; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		break;
	default:
		dev_warn(&adapter->pdev->dev, "Unknown get statistics mode\n");
		*ret = -EIO;
	}
	return data;
}