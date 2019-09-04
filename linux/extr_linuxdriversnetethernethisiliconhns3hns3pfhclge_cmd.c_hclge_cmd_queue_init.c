#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* desc_num; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {void* desc_num; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_5__ csq; int /*<<< orphan*/  tx_timeout; TYPE_1__ crq; } ;
struct TYPE_9__ {TYPE_3__ cmq; } ;
struct hclge_dev {TYPE_4__ hw; TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMDQ_TX_TIMEOUT ; 
 void* HCLGE_NIC_CMQ_DESC_NUM ; 
 int /*<<< orphan*/  HCLGE_TYPE_CRQ ; 
 int /*<<< orphan*/  HCLGE_TYPE_CSQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_alloc_cmd_queue (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_free_cmd_desc (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hclge_cmd_queue_init(struct hclge_dev *hdev)
{
	int ret;

	/* Setup the lock for command queue */
	spin_lock_init(&hdev->hw.cmq.csq.lock);
	spin_lock_init(&hdev->hw.cmq.crq.lock);

	/* Setup the queue entries for use cmd queue */
	hdev->hw.cmq.csq.desc_num = HCLGE_NIC_CMQ_DESC_NUM;
	hdev->hw.cmq.crq.desc_num = HCLGE_NIC_CMQ_DESC_NUM;

	/* Setup Tx write back timeout */
	hdev->hw.cmq.tx_timeout = HCLGE_CMDQ_TX_TIMEOUT;

	/* Setup queue rings */
	ret = hclge_alloc_cmd_queue(hdev, HCLGE_TYPE_CSQ);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"CSQ ring setup error %d\n", ret);
		return ret;
	}

	ret = hclge_alloc_cmd_queue(hdev, HCLGE_TYPE_CRQ);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"CRQ ring setup error %d\n", ret);
		goto err_csq;
	}

	return 0;
err_csq:
	hclge_free_cmd_desc(&hdev->hw.cmq.csq);
	return ret;
}