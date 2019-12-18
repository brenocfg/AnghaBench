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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int rss_algo; int /*<<< orphan*/ * rss_indirection_tbl; int /*<<< orphan*/  rss_hash_key; struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETH_RSS_HASH_NO_CHANGE 130 
#define  ETH_RSS_HASH_TOP 129 
#define  ETH_RSS_HASH_XOR 128 
 int HCLGE_RSS_HASH_ALGO_SIMPLE ; 
 int HCLGE_RSS_HASH_ALGO_TOEPLITZ ; 
 int HCLGE_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGE_RSS_KEY_SIZE ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_rss_algo_key (struct hclge_dev*,int,int const*) ; 
 int hclge_set_rss_indir_table (struct hclge_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_rss(struct hnae3_handle *handle, const u32 *indir,
			 const  u8 *key, const  u8 hfunc)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u8 hash_algo;
	int ret, i;

	/* Set the RSS Hash Key if specififed by the user */
	if (key) {
		switch (hfunc) {
		case ETH_RSS_HASH_TOP:
			hash_algo = HCLGE_RSS_HASH_ALGO_TOEPLITZ;
			break;
		case ETH_RSS_HASH_XOR:
			hash_algo = HCLGE_RSS_HASH_ALGO_SIMPLE;
			break;
		case ETH_RSS_HASH_NO_CHANGE:
			hash_algo = vport->rss_algo;
			break;
		default:
			return -EINVAL;
		}

		ret = hclge_set_rss_algo_key(hdev, hash_algo, key);
		if (ret)
			return ret;

		/* Update the shadow RSS key with user specified qids */
		memcpy(vport->rss_hash_key, key, HCLGE_RSS_KEY_SIZE);
		vport->rss_algo = hash_algo;
	}

	/* Update the shadow RSS table with user specified qids */
	for (i = 0; i < HCLGE_RSS_IND_TBL_SIZE; i++)
		vport->rss_indirection_tbl[i] = indir[i];

	/* Update the hardware */
	return hclge_set_rss_indir_table(hdev, vport->rss_indirection_tbl);
}