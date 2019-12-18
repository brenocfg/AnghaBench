#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hclge_tx_buff_alloc_cmd {int /*<<< orphan*/ * tx_pkt_buff; } ;
struct hclge_rx_priv_wl_buf {TYPE_4__* tc_wl; } ;
struct hclge_rx_priv_buff_cmd {int /*<<< orphan*/  shared_buf; int /*<<< orphan*/ * buf_num; } ;
struct TYPE_6__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct hclge_rx_com_wl {TYPE_2__ com_wl; } ;
struct hclge_rx_com_thrd {TYPE_1__* com_thrd; } ;
struct hclge_dev {TYPE_3__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; int /*<<< orphan*/  flag; } ;
typedef  enum hclge_opcode_type { ____Placeholder_hclge_opcode_type } hclge_opcode_type ;
struct TYPE_8__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMD_FLAG_NEXT ; 
 int HCLGE_MAX_TC_NUM ; 
 int HCLGE_OPC_RX_COM_THRD_ALLOC ; 
 int HCLGE_OPC_RX_COM_WL_ALLOC ; 
 int HCLGE_OPC_RX_GBL_PKT_CNT ; 
 int HCLGE_OPC_RX_PRIV_BUFF_ALLOC ; 
 int HCLGE_OPC_RX_PRIV_WL_ALLOC ; 
 int HCLGE_OPC_TX_BUFF_ALLOC ; 
 int HCLGE_TC_NUM_ONE_DESC ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int,int) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 

__attribute__((used)) static void hclge_dbg_dump_qos_buf_cfg(struct hclge_dev *hdev)
{
	struct hclge_tx_buff_alloc_cmd *tx_buf_cmd;
	struct hclge_rx_priv_buff_cmd *rx_buf_cmd;
	struct hclge_rx_priv_wl_buf *rx_priv_wl;
	struct hclge_rx_com_wl *rx_packet_cnt;
	struct hclge_rx_com_thrd *rx_com_thrd;
	struct hclge_rx_com_wl *rx_com_wl;
	enum hclge_opcode_type cmd;
	struct hclge_desc desc[2];
	int i, ret;

	cmd = HCLGE_OPC_TX_BUFF_ALLOC;
	hclge_cmd_setup_basic_desc(desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 1);
	if (ret)
		goto err_qos_cmd_send;

	dev_info(&hdev->pdev->dev, "dump qos buf cfg\n");

	tx_buf_cmd = (struct hclge_tx_buff_alloc_cmd *)desc[0].data;
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		dev_info(&hdev->pdev->dev, "tx_packet_buf_tc_%d: 0x%x\n", i,
			 tx_buf_cmd->tx_pkt_buff[i]);

	cmd = HCLGE_OPC_RX_PRIV_BUFF_ALLOC;
	hclge_cmd_setup_basic_desc(desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 1);
	if (ret)
		goto err_qos_cmd_send;

	dev_info(&hdev->pdev->dev, "\n");
	rx_buf_cmd = (struct hclge_rx_priv_buff_cmd *)desc[0].data;
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		dev_info(&hdev->pdev->dev, "rx_packet_buf_tc_%d: 0x%x\n", i,
			 rx_buf_cmd->buf_num[i]);

	dev_info(&hdev->pdev->dev, "rx_share_buf: 0x%x\n",
		 rx_buf_cmd->shared_buf);

	cmd = HCLGE_OPC_RX_COM_WL_ALLOC;
	hclge_cmd_setup_basic_desc(desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 1);
	if (ret)
		goto err_qos_cmd_send;

	rx_com_wl = (struct hclge_rx_com_wl *)desc[0].data;
	dev_info(&hdev->pdev->dev, "\n");
	dev_info(&hdev->pdev->dev, "rx_com_wl: high: 0x%x, low: 0x%x\n",
		 rx_com_wl->com_wl.high, rx_com_wl->com_wl.low);

	cmd = HCLGE_OPC_RX_GBL_PKT_CNT;
	hclge_cmd_setup_basic_desc(desc, cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 1);
	if (ret)
		goto err_qos_cmd_send;

	rx_packet_cnt = (struct hclge_rx_com_wl *)desc[0].data;
	dev_info(&hdev->pdev->dev,
		 "rx_global_packet_cnt: high: 0x%x, low: 0x%x\n",
		 rx_packet_cnt->com_wl.high, rx_packet_cnt->com_wl.low);
	dev_info(&hdev->pdev->dev, "\n");

	if (!hnae3_dev_dcb_supported(hdev)) {
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports rx priv wl\n");
		return;
	}
	cmd = HCLGE_OPC_RX_PRIV_WL_ALLOC;
	hclge_cmd_setup_basic_desc(&desc[0], cmd, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	if (ret)
		goto err_qos_cmd_send;

	rx_priv_wl = (struct hclge_rx_priv_wl_buf *)desc[0].data;
	for (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_priv_wl_tc_%d: high: 0x%x, low: 0x%x\n", i,
			 rx_priv_wl->tc_wl[i].high, rx_priv_wl->tc_wl[i].low);

	rx_priv_wl = (struct hclge_rx_priv_wl_buf *)desc[1].data;
	for (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_priv_wl_tc_%d: high: 0x%x, low: 0x%x\n",
			 i + HCLGE_TC_NUM_ONE_DESC,
			 rx_priv_wl->tc_wl[i].high, rx_priv_wl->tc_wl[i].low);

	cmd = HCLGE_OPC_RX_COM_THRD_ALLOC;
	hclge_cmd_setup_basic_desc(&desc[0], cmd, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], cmd, true);
	ret = hclge_cmd_send(&hdev->hw, desc, 2);
	if (ret)
		goto err_qos_cmd_send;

	dev_info(&hdev->pdev->dev, "\n");
	rx_com_thrd = (struct hclge_rx_com_thrd *)desc[0].data;
	for (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_com_thrd_tc_%d: high: 0x%x, low: 0x%x\n", i,
			 rx_com_thrd->com_thrd[i].high,
			 rx_com_thrd->com_thrd[i].low);

	rx_com_thrd = (struct hclge_rx_com_thrd *)desc[1].data;
	for (i = 0; i < HCLGE_TC_NUM_ONE_DESC; i++)
		dev_info(&hdev->pdev->dev,
			 "rx_com_thrd_tc_%d: high: 0x%x, low: 0x%x\n",
			 i + HCLGE_TC_NUM_ONE_DESC,
			 rx_com_thrd->com_thrd[i].high,
			 rx_com_thrd->com_thrd[i].low);
	return;

err_qos_cmd_send:
	dev_err(&hdev->pdev->dev,
		"dump qos buf cfg fail(0x%x), ret = %d\n", cmd, ret);
}