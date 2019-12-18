#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  lock; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_11__ {TYPE_3__ csq; TYPE_2__ crq; } ;
struct TYPE_13__ {TYPE_4__ cmq; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; scalar_t__ tail; scalar_t__ head; struct hclgevf_dev* hdev; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; TYPE_5__* pdev; int /*<<< orphan*/  fw_version; TYPE_6__ hw; TYPE_1__ arq; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGEVF_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE0_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE0_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE1_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE1_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE2_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE2_SHIFT ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE3_MASK ; 
 int /*<<< orphan*/  HNAE3_FW_VERSION_BYTE3_SHIFT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_cmd_init_regs (TYPE_6__*) ; 
 int hclgevf_cmd_query_firmware_version (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ hclgevf_is_reset_pending (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int hclgevf_cmd_init(struct hclgevf_dev *hdev)
{
	u32 version;
	int ret;

	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);

	/* initialize the pointers of async rx queue of mailbox */
	hdev->arq.hdev = hdev;
	hdev->arq.head = 0;
	hdev->arq.tail = 0;
	atomic_set(&hdev->arq.count, 0);
	hdev->hw.cmq.csq.next_to_clean = 0;
	hdev->hw.cmq.csq.next_to_use = 0;
	hdev->hw.cmq.crq.next_to_clean = 0;
	hdev->hw.cmq.crq.next_to_use = 0;

	hclgevf_cmd_init_regs(&hdev->hw);

	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	clear_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);

	/* Check if there is new reset pending, because the higher level
	 * reset may happen when lower level reset is being processed.
	 */
	if (hclgevf_is_reset_pending(hdev)) {
		ret = -EBUSY;
		goto err_cmd_init;
	}

	/* get firmware version */
	ret = hclgevf_cmd_query_firmware_version(&hdev->hw, &version);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to query firmware version\n", ret);
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

	return 0;

err_cmd_init:
	set_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state);

	return ret;
}