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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {TYPE_1__* pdev; } ;
struct hclgevf_rss_cfg {int /*<<< orphan*/ * rss_indirection_tbl; int /*<<< orphan*/  rss_hash_key; int /*<<< orphan*/  hash_algo; } ;
struct hclgevf_dev {struct hclgevf_rss_cfg rss_cfg; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETH_RSS_HASH_NO_CHANGE 130 
#define  ETH_RSS_HASH_TOP 129 
#define  ETH_RSS_HASH_XOR 128 
 int /*<<< orphan*/  HCLGEVF_RSS_HASH_ALGO_SIMPLE ; 
 int /*<<< orphan*/  HCLGEVF_RSS_HASH_ALGO_TOEPLITZ ; 
 int HCLGEVF_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGEVF_RSS_KEY_SIZE ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_set_rss_algo_key (struct hclgevf_dev*,int /*<<< orphan*/ ,int const*) ; 
 int hclgevf_set_rss_indir_table (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_set_rss(struct hnae3_handle *handle, const u32 *indir,
			   const u8 *key, const u8 hfunc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	int ret, i;

	if (handle->pdev->revision >= 0x21) {
		/* Set the RSS Hash Key if specififed by the user */
		if (key) {
			switch (hfunc) {
			case ETH_RSS_HASH_TOP:
				rss_cfg->hash_algo =
					HCLGEVF_RSS_HASH_ALGO_TOEPLITZ;
				break;
			case ETH_RSS_HASH_XOR:
				rss_cfg->hash_algo =
					HCLGEVF_RSS_HASH_ALGO_SIMPLE;
				break;
			case ETH_RSS_HASH_NO_CHANGE:
				break;
			default:
				return -EINVAL;
			}

			ret = hclgevf_set_rss_algo_key(hdev, rss_cfg->hash_algo,
						       key);
			if (ret)
				return ret;

			/* Update the shadow RSS key with user specified qids */
			memcpy(rss_cfg->rss_hash_key, key,
			       HCLGEVF_RSS_KEY_SIZE);
		}
	}

	/* update the shadow RSS table with user specified qids */
	for (i = 0; i < HCLGEVF_RSS_IND_TBL_SIZE; i++)
		rss_cfg->rss_indirection_tbl[i] = indir[i];

	/* update the hardware */
	return hclgevf_set_rss_indir_table(hdev);
}