#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  lock; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_9__ {TYPE_2__ csq; TYPE_1__ crq; } ;
struct TYPE_11__ {TYPE_3__ cmq; } ;
struct hclge_dev {TYPE_4__* pdev; int /*<<< orphan*/  fw_version; TYPE_5__ hw; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_cmd_init_regs (TYPE_5__*) ; 
 int hclge_cmd_query_firmware_version (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int hclge_cmd_init(struct hclge_dev *hdev)
{
	u32 version;
	int ret;

	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock_bh(&hdev->hw.cmq.crq.lock);

	hdev->hw.cmq.csq.next_to_clean = 0;
	hdev->hw.cmq.csq.next_to_use = 0;
	hdev->hw.cmq.crq.next_to_clean = 0;
	hdev->hw.cmq.crq.next_to_use = 0;

	hclge_cmd_init_regs(&hdev->hw);
	clear_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	spin_unlock_bh(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	ret = hclge_cmd_query_firmware_version(&hdev->hw, &version);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"firmware version query failed %d\n", ret);
		return ret;
	}
	hdev->fw_version = version;

	dev_info(&hdev->pdev->dev, "The firmware version is %08x\n", version);

	return 0;
}