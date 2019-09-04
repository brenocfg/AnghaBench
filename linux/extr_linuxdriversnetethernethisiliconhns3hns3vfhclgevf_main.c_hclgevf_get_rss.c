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
 int hclgevf_get_rss_hw_cfg (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_get_rss(struct hnae3_handle *handle, u32 *indir, u8 *key,
			   u8 *hfunc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	int i;

	if (indir)
		for (i = 0; i < HCLGEVF_RSS_IND_TBL_SIZE; i++)
			indir[i] = rss_cfg->rss_indirection_tbl[i];

	return hclgevf_get_rss_hw_cfg(handle, hfunc, key);
}