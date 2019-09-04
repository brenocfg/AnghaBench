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
typedef  int /*<<< orphan*/  u8 ;
struct hclge_rss_indirection_table_cmd {int /*<<< orphan*/ * rss_result; void* rss_set_bitmap; void* start_table_index; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_RSS_INDIR_TABLE ; 
 int HCLGE_RSS_CFG_TBL_NUM ; 
 int HCLGE_RSS_CFG_TBL_SIZE ; 
 int HCLGE_RSS_SET_BITMAP_MSK ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_rss_indir_table(struct hclge_dev *hdev, const u8 *indir)
{
	struct hclge_rss_indirection_table_cmd *req;
	struct hclge_desc desc;
	int i, j;
	int ret;

	req = (struct hclge_rss_indirection_table_cmd *)desc.data;

	for (i = 0; i < HCLGE_RSS_CFG_TBL_NUM; i++) {
		hclge_cmd_setup_basic_desc
			(&desc, HCLGE_OPC_RSS_INDIR_TABLE, false);

		req->start_table_index =
			cpu_to_le16(i * HCLGE_RSS_CFG_TBL_SIZE);
		req->rss_set_bitmap = cpu_to_le16(HCLGE_RSS_SET_BITMAP_MSK);

		for (j = 0; j < HCLGE_RSS_CFG_TBL_SIZE; j++)
			req->rss_result[j] =
				indir[i * HCLGE_RSS_CFG_TBL_SIZE + j];

		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"Configure rss indir table fail,status = %d\n",
				ret);
			return ret;
		}
	}
	return 0;
}