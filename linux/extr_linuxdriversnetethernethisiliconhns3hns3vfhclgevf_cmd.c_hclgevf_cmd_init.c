#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  flag; } ;
struct TYPE_9__ {TYPE_4__ csq; TYPE_4__ crq; int /*<<< orphan*/  tx_timeout; } ;
struct TYPE_11__ {TYPE_3__ cmq; } ;
struct TYPE_7__ {scalar_t__ count; scalar_t__ tail; scalar_t__ head; struct hclgevf_dev* hdev; } ;
struct hclgevf_dev {TYPE_6__ hw; TYPE_2__* pdev; int /*<<< orphan*/  fw_version; TYPE_1__ arq; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_CMDQ_TX_TIMEOUT ; 
 int /*<<< orphan*/  HCLGEVF_TYPE_CRQ ; 
 int /*<<< orphan*/  HCLGEVF_TYPE_CSQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hclgevf_cmd_query_firmware_version (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclgevf_free_cmd_desc (TYPE_4__*) ; 
 int hclgevf_init_cmd_queue (struct hclgevf_dev*,TYPE_4__*) ; 

int hclgevf_cmd_init(struct hclgevf_dev *hdev)
{
	u32 version;
	int ret;

	/* setup Tx write back timeout */
	hdev->hw.cmq.tx_timeout = HCLGEVF_CMDQ_TX_TIMEOUT;

	/* setup queue CSQ/CRQ rings */
	hdev->hw.cmq.csq.flag = HCLGEVF_TYPE_CSQ;
	ret = hclgevf_init_cmd_queue(hdev, &hdev->hw.cmq.csq);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize CSQ ring\n", ret);
		return ret;
	}

	hdev->hw.cmq.crq.flag = HCLGEVF_TYPE_CRQ;
	ret = hclgevf_init_cmd_queue(hdev, &hdev->hw.cmq.crq);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to initialize CRQ ring\n", ret);
		goto err_csq;
	}

	/* initialize the pointers of async rx queue of mailbox */
	hdev->arq.hdev = hdev;
	hdev->arq.head = 0;
	hdev->arq.tail = 0;
	hdev->arq.count = 0;

	/* get firmware version */
	ret = hclgevf_cmd_query_firmware_version(&hdev->hw, &version);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"failed(%d) to query firmware version\n", ret);
		goto err_crq;
	}
	hdev->fw_version = version;

	dev_info(&hdev->pdev->dev, "The firmware version is %08x\n", version);

	return 0;
err_crq:
	hclgevf_free_cmd_desc(&hdev->hw.cmq.crq);
err_csq:
	hclgevf_free_cmd_desc(&hdev->hw.cmq.csq);

	return ret;
}