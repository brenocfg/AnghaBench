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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_rss_cfg {int /*<<< orphan*/ * rss_indirection_tbl; } ;
struct hclgevf_dev {struct hclgevf_rss_cfg rss_cfg; } ;

/* Variables and functions */
 int HCLGEVF_RSS_IND_TBL_SIZE ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_set_rss_indir_table (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_set_rss(struct hnae3_handle *handle, const u32 *indir,
			   const  u8 *key, const  u8 hfunc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	int i;

	/* update the shadow RSS table with user specified qids */
	for (i = 0; i < HCLGEVF_RSS_IND_TBL_SIZE; i++)
		rss_cfg->rss_indirection_tbl[i] = indir[i];

	/* update the hardware */
	return hclgevf_set_rss_indir_table(hdev);
}