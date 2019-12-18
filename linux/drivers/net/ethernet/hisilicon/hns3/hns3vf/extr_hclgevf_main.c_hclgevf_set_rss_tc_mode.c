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
typedef  unsigned int u16 ;
struct hclgevf_rss_tc_mode_cmd {int /*<<< orphan*/ * rss_tc_mode; } ;
struct hclgevf_dev {int hw_tc_map; TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int HCLGEVF_MAX_TC_NUM ; 
 int /*<<< orphan*/  HCLGEVF_OPC_RSS_TC_MODE ; 
 int /*<<< orphan*/  HCLGEVF_RSS_TC_OFFSET_M ; 
 int /*<<< orphan*/  HCLGEVF_RSS_TC_OFFSET_S ; 
 int /*<<< orphan*/  HCLGEVF_RSS_TC_SIZE_M ; 
 int /*<<< orphan*/  HCLGEVF_RSS_TC_SIZE_S ; 
 int /*<<< orphan*/  HCLGEVF_RSS_TC_VALID_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int ilog2 (unsigned int) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 

__attribute__((used)) static int hclgevf_set_rss_tc_mode(struct hclgevf_dev *hdev,  u16 rss_size)
{
	struct hclgevf_rss_tc_mode_cmd *req;
	u16 tc_offset[HCLGEVF_MAX_TC_NUM];
	u16 tc_valid[HCLGEVF_MAX_TC_NUM];
	u16 tc_size[HCLGEVF_MAX_TC_NUM];
	struct hclgevf_desc desc;
	u16 roundup_size;
	int status;
	unsigned int i;

	req = (struct hclgevf_rss_tc_mode_cmd *)desc.data;

	roundup_size = roundup_pow_of_two(rss_size);
	roundup_size = ilog2(roundup_size);

	for (i = 0; i < HCLGEVF_MAX_TC_NUM; i++) {
		tc_valid[i] = !!(hdev->hw_tc_map & BIT(i));
		tc_size[i] = roundup_size;
		tc_offset[i] = rss_size * i;
	}

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_RSS_TC_MODE, false);
	for (i = 0; i < HCLGEVF_MAX_TC_NUM; i++) {
		hnae3_set_bit(req->rss_tc_mode[i], HCLGEVF_RSS_TC_VALID_B,
			      (tc_valid[i] & 0x1));
		hnae3_set_field(req->rss_tc_mode[i], HCLGEVF_RSS_TC_SIZE_M,
				HCLGEVF_RSS_TC_SIZE_S, tc_size[i]);
		hnae3_set_field(req->rss_tc_mode[i], HCLGEVF_RSS_TC_OFFSET_M,
				HCLGEVF_RSS_TC_OFFSET_S, tc_offset[i]);
	}
	status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_err(&hdev->pdev->dev,
			"VF failed(=%d) to set rss tc mode\n", status);

	return status;
}