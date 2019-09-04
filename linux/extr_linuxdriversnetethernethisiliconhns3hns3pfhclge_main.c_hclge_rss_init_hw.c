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
typedef  int u16 ;
struct hclge_vport {int alloc_rss_size; int /*<<< orphan*/  rss_algo; int /*<<< orphan*/ * rss_hash_key; int /*<<< orphan*/ * rss_indirection_tbl; } ;
struct hclge_dev {int hw_tc_map; TYPE_1__* pdev; struct hclge_vport* vport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int HCLGE_MAX_TC_NUM ; 
 int HCLGE_RSS_TC_SIZE_7 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_set_rss_algo_key (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hclge_set_rss_indir_table (struct hclge_dev*,int /*<<< orphan*/ *) ; 
 int hclge_set_rss_input_tuple (struct hclge_dev*) ; 
 int hclge_set_rss_tc_mode (struct hclge_dev*,int*,int*,int*) ; 
 int ilog2 (int) ; 
 int roundup_pow_of_two (int) ; 

int hclge_rss_init_hw(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	u8 *rss_indir = vport[0].rss_indirection_tbl;
	u16 rss_size = vport[0].alloc_rss_size;
	u8 *key = vport[0].rss_hash_key;
	u8 hfunc = vport[0].rss_algo;
	u16 tc_offset[HCLGE_MAX_TC_NUM];
	u16 tc_valid[HCLGE_MAX_TC_NUM];
	u16 tc_size[HCLGE_MAX_TC_NUM];
	u16 roundup_size;
	int i, ret;

	ret = hclge_set_rss_indir_table(hdev, rss_indir);
	if (ret)
		return ret;

	ret = hclge_set_rss_algo_key(hdev, hfunc, key);
	if (ret)
		return ret;

	ret = hclge_set_rss_input_tuple(hdev);
	if (ret)
		return ret;

	/* Each TC have the same queue size, and tc_size set to hardware is
	 * the log2 of roundup power of two of rss_size, the acutal queue
	 * size is limited by indirection table.
	 */
	if (rss_size > HCLGE_RSS_TC_SIZE_7 || rss_size == 0) {
		dev_err(&hdev->pdev->dev,
			"Configure rss tc size failed, invalid TC_SIZE = %d\n",
			rss_size);
		return -EINVAL;
	}

	roundup_size = roundup_pow_of_two(rss_size);
	roundup_size = ilog2(roundup_size);

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		tc_valid[i] = 0;

		if (!(hdev->hw_tc_map & BIT(i)))
			continue;

		tc_valid[i] = 1;
		tc_size[i] = roundup_size;
		tc_offset[i] = rss_size * i;
	}

	return hclge_set_rss_tc_mode(hdev, tc_valid, tc_size, tc_offset);
}