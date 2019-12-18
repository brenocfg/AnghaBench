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
typedef  size_t u8 ;
typedef  int u32 ;
struct hclge_tx_buff_alloc_cmd {int /*<<< orphan*/ * tx_pkt_buff; } ;
struct hclge_pkt_buf_alloc {TYPE_1__* priv_buf; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int tx_buf_size; } ;

/* Variables and functions */
 int HCLGE_BUF_SIZE_UNIT_SHIFT ; 
 int HCLGE_BUF_SIZE_UPDATE_EN_MSK ; 
 size_t HCLGE_MAX_TC_NUM ; 
 int /*<<< orphan*/  HCLGE_OPC_TX_BUFF_ALLOC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  hclge_cmd_alloc_tx_buff(struct hclge_dev *hdev,
				    struct hclge_pkt_buf_alloc *buf_alloc)
{
/* TX buffer size is unit by 128 byte */
#define HCLGE_BUF_SIZE_UNIT_SHIFT	7
#define HCLGE_BUF_SIZE_UPDATE_EN_MSK	BIT(15)
	struct hclge_tx_buff_alloc_cmd *req;
	struct hclge_desc desc;
	int ret;
	u8 i;

	req = (struct hclge_tx_buff_alloc_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TX_BUFF_ALLOC, 0);
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		u32 buf_size = buf_alloc->priv_buf[i].tx_buf_size;

		req->tx_pkt_buff[i] =
			cpu_to_le16((buf_size >> HCLGE_BUF_SIZE_UNIT_SHIFT) |
				     HCLGE_BUF_SIZE_UPDATE_EN_MSK);
	}

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev, "tx buffer alloc cmd failed %d.\n",
			ret);

	return ret;
}