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
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {TYPE_1__* pdev; } ;
struct hclgevf_rss_cfg {int hash_algo; int /*<<< orphan*/ * rss_indirection_tbl; int /*<<< orphan*/  rss_hash_key; } ;
struct hclgevf_dev {struct hclgevf_rss_cfg rss_cfg; } ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_UNKNOWN ; 
 int /*<<< orphan*/  ETH_RSS_HASH_XOR ; 
#define  HCLGEVF_RSS_HASH_ALGO_SIMPLE 129 
#define  HCLGEVF_RSS_HASH_ALGO_TOEPLITZ 128 
 int HCLGEVF_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGEVF_RSS_KEY_SIZE ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_get_rss_hash_key (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_get_rss(struct hnae3_handle *handle, u32 *indir, u8 *key,
			   u8 *hfunc)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	int i, ret;

	if (handle->pdev->revision >= 0x21) {
		/* Get hash algorithm */
		if (hfunc) {
			switch (rss_cfg->hash_algo) {
			case HCLGEVF_RSS_HASH_ALGO_TOEPLITZ:
				*hfunc = ETH_RSS_HASH_TOP;
				break;
			case HCLGEVF_RSS_HASH_ALGO_SIMPLE:
				*hfunc = ETH_RSS_HASH_XOR;
				break;
			default:
				*hfunc = ETH_RSS_HASH_UNKNOWN;
				break;
			}
		}

		/* Get the RSS Key required by the user */
		if (key)
			memcpy(key, rss_cfg->rss_hash_key,
			       HCLGEVF_RSS_KEY_SIZE);
	} else {
		if (hfunc)
			*hfunc = ETH_RSS_HASH_TOP;
		if (key) {
			ret = hclgevf_get_rss_hash_key(hdev);
			if (ret)
				return ret;
			memcpy(key, rss_cfg->rss_hash_key,
			       HCLGEVF_RSS_KEY_SIZE);
		}
	}

	if (indir)
		for (i = 0; i < HCLGEVF_RSS_IND_TBL_SIZE; i++)
			indir[i] = rss_cfg->rss_indirection_tbl[i];

	return 0;
}