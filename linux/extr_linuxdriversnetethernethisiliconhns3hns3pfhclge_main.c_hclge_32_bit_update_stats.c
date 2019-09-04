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
struct hclge_32_bit_stats {int /*<<< orphan*/  igu_rx_no_sof_pkt; int /*<<< orphan*/  igu_rx_no_eof_pkt; int /*<<< orphan*/  igu_rx_err_pkt; int /*<<< orphan*/  egu_tx_1588_pkt; } ;
struct TYPE_3__ {struct hclge_32_bit_stats all_32_bit_stats; } ;
struct hclge_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_1__ hw_stats; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_STATS_32_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_reset_partial_32bit_counter (struct hclge_32_bit_stats*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hclge_32_bit_update_stats(struct hclge_dev *hdev)
{
#define HCLGE_32_BIT_CMD_NUM 8
#define HCLGE_32_BIT_RTN_DATANUM 8

	struct hclge_desc desc[HCLGE_32_BIT_CMD_NUM];
	struct hclge_32_bit_stats *all_32_bit_stats;
	__le32 *desc_data;
	int i, k, n;
	u64 *data;
	int ret;

	all_32_bit_stats = &hdev->hw_stats.all_32_bit_stats;
	data = (u64 *)(&all_32_bit_stats->egu_tx_1588_pkt);

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_STATS_32_BIT, true);
	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_32_BIT_CMD_NUM);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get 32 bit pkt stats fail, status = %d.\n", ret);

		return ret;
	}

	hclge_reset_partial_32bit_counter(all_32_bit_stats);
	for (i = 0; i < HCLGE_32_BIT_CMD_NUM; i++) {
		if (unlikely(i == 0)) {
			__le16 *desc_data_16bit;

			all_32_bit_stats->igu_rx_err_pkt +=
				le32_to_cpu(desc[i].data[0]);

			desc_data_16bit = (__le16 *)&desc[i].data[1];
			all_32_bit_stats->igu_rx_no_eof_pkt +=
				le16_to_cpu(*desc_data_16bit);

			desc_data_16bit++;
			all_32_bit_stats->igu_rx_no_sof_pkt +=
				le16_to_cpu(*desc_data_16bit);

			desc_data = &desc[i].data[2];
			n = HCLGE_32_BIT_RTN_DATANUM - 4;
		} else {
			desc_data = (__le32 *)&desc[i];
			n = HCLGE_32_BIT_RTN_DATANUM;
		}
		for (k = 0; k < n; k++) {
			*data++ += le32_to_cpu(*desc_data);
			desc_data++;
		}
	}

	return 0;
}