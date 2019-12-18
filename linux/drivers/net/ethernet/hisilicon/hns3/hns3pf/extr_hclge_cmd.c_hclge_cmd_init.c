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
struct hclge_dev {int /*<<< orphan*/  state; TYPE_4__* pdev; int /*<<< orphan*/  fw_version; TYPE_5__ hw; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE0_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE0_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE1_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE1_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE2_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE2_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE3_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE3_SHIFT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_cmd_init_regs (TYPE_5__*) ; 
 int hclge_cmd_query_firmware_version (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int hclge_firmware_compat_config (struct hclge_dev*) ; 
 scalar_t__ hclge_is_reset_pending (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int hclge_cmd_init(struct hclge_dev *hdev)
{
	u32 version;
	int ret;

	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);

	hdev->hw.cmq.csq.next_to_clean = 0;
	hdev->hw.cmq.csq.next_to_use = 0;
	hdev->hw.cmq.crq.next_to_clean = 0;
	hdev->hw.cmq.crq.next_to_use = 0;

	hclge_cmd_init_regs(&hdev->hw);

	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	clear_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	/* Check if there is new reset pending, because the higher level
	 * reset may happen when lower level reset is being processed.
	 */
	if ((hclge_is_reset_pending(hdev))) {
		ret = -EBUSY;
		goto err_cmd_init;
	}

	ret = hclge_cmd_query_firmware_version(&hdev->hw, &version);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"firmware version query failed %d\n", ret);
		goto err_cmd_init;
	}
	hdev->fw_version = version;

	dev_info(&hdev->pdev->dev, "The firmware version is %lu.%lu.%lu.%lu\n",
		 hnae3_get_field(version, HNAE3_FW_VERSION_BYTE3_MASK,
				 HNAE3_FW_VERSION_BYTE3_SHIFT),
		 hnae3_get_field(version, HNAE3_FW_VERSION_BYTE2_MASK,
				 HNAE3_FW_VERSION_BYTE2_SHIFT),
		 hnae3_get_field(version, HNAE3_FW_VERSION_BYTE1_MASK,
				 HNAE3_FW_VERSION_BYTE1_SHIFT),
		 hnae3_get_field(version, HNAE3_FW_VERSION_BYTE0_MASK,
				 HNAE3_FW_VERSION_BYTE0_SHIFT));

	/* ask the firmware to enable some features, driver can work without
	 * it.
	 */
	ret = hclge_firmware_compat_config(hdev);
	if (ret)
		dev_warn(&hdev->pdev->dev,
			 "Firmware compatible features not enabled(%d).\n",
			 ret);

	return 0;

err_cmd_init:
	set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);

	return ret;
}