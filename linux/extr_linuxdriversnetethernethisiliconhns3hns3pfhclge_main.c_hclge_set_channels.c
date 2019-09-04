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
typedef  int u32 ;
typedef  int u16 ;
struct hnae3_knic_private_info {int rss_size; int num_tqps; int num_tc; int /*<<< orphan*/  num_desc; } ;
struct hnae3_handle {int dummy; } ;
struct TYPE_3__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {struct hclge_dev* back; TYPE_1__ nic; } ;
struct hclge_dev {int hw_tc_map; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCLGE_MAX_TC_NUM ; 
 int HCLGE_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_knic_setup (struct hclge_vport*,int,int /*<<< orphan*/ ) ; 
 int hclge_map_tqp_to_vport (struct hclge_dev*,struct hclge_vport*) ; 
 int /*<<< orphan*/  hclge_release_tqp (struct hclge_vport*) ; 
 int hclge_set_rss (struct hnae3_handle*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclge_set_rss_tc_mode (struct hclge_dev*,int*,int*,int*) ; 
 int hclge_tm_schd_init (struct hclge_dev*) ; 
 int ilog2 (int) ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static int hclge_set_channels(struct hnae3_handle *handle, u32 new_tqps_num)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hclge_dev *hdev = vport->back;
	int cur_rss_size = kinfo->rss_size;
	int cur_tqps = kinfo->num_tqps;
	u16 tc_offset[HCLGE_MAX_TC_NUM];
	u16 tc_valid[HCLGE_MAX_TC_NUM];
	u16 tc_size[HCLGE_MAX_TC_NUM];
	u16 roundup_size;
	u32 *rss_indir;
	int ret, i;

	/* Free old tqps, and reallocate with new tqp number when nic setup */
	hclge_release_tqp(vport);

	ret = hclge_knic_setup(vport, new_tqps_num, kinfo->num_desc);
	if (ret) {
		dev_err(&hdev->pdev->dev, "setup nic fail, ret =%d\n", ret);
		return ret;
	}

	ret = hclge_map_tqp_to_vport(hdev, vport);
	if (ret) {
		dev_err(&hdev->pdev->dev, "map vport tqp fail, ret =%d\n", ret);
		return ret;
	}

	ret = hclge_tm_schd_init(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev, "tm schd init fail, ret =%d\n", ret);
		return ret;
	}

	roundup_size = roundup_pow_of_two(kinfo->rss_size);
	roundup_size = ilog2(roundup_size);
	/* Set the RSS TC mode according to the new RSS size */
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		tc_valid[i] = 0;

		if (!(hdev->hw_tc_map & BIT(i)))
			continue;

		tc_valid[i] = 1;
		tc_size[i] = roundup_size;
		tc_offset[i] = kinfo->rss_size * i;
	}
	ret = hclge_set_rss_tc_mode(hdev, tc_valid, tc_size, tc_offset);
	if (ret)
		return ret;

	/* Reinitializes the rss indirect table according to the new RSS size */
	rss_indir = kcalloc(HCLGE_RSS_IND_TBL_SIZE, sizeof(u32), GFP_KERNEL);
	if (!rss_indir)
		return -ENOMEM;

	for (i = 0; i < HCLGE_RSS_IND_TBL_SIZE; i++)
		rss_indir[i] = i % kinfo->rss_size;

	ret = hclge_set_rss(handle, rss_indir, NULL, 0);
	if (ret)
		dev_err(&hdev->pdev->dev, "set rss indir table fail, ret=%d\n",
			ret);

	kfree(rss_indir);

	if (!ret)
		dev_info(&hdev->pdev->dev,
			 "Channels changed, rss_size from %d to %d, tqps from %d to %d",
			 cur_rss_size, kinfo->rss_size,
			 cur_tqps, kinfo->rss_size * kinfo->num_tc);

	return ret;
}