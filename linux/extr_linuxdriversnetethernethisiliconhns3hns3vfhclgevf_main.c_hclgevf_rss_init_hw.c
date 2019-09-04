#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hclgevf_rss_cfg {int rss_size; int* rss_indirection_tbl; } ;
struct hclgevf_dev {int rss_size_max; struct hclgevf_rss_cfg rss_cfg; } ;

/* Variables and functions */
 int HCLGEVF_RSS_IND_TBL_SIZE ; 
 int hclgevf_set_rss_indir_table (struct hclgevf_dev*) ; 
 int hclgevf_set_rss_tc_mode (struct hclgevf_dev*,int) ; 

__attribute__((used)) static int hclgevf_rss_init_hw(struct hclgevf_dev *hdev)
{
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	int i, ret;

	rss_cfg->rss_size = hdev->rss_size_max;

	/* Initialize RSS indirect table for each vport */
	for (i = 0; i < HCLGEVF_RSS_IND_TBL_SIZE; i++)
		rss_cfg->rss_indirection_tbl[i] = i % hdev->rss_size_max;

	ret = hclgevf_set_rss_indir_table(hdev);
	if (ret)
		return ret;

	return hclgevf_set_rss_tc_mode(hdev, hdev->rss_size_max);
}