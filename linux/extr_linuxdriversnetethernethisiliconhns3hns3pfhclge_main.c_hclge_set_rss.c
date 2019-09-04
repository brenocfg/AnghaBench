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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int /*<<< orphan*/ * rss_indirection_tbl; scalar_t__ rss_algo; int /*<<< orphan*/  rss_hash_key; struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 scalar_t__ HCLGE_RSS_HASH_ALGO_TOEPLITZ ; 
 int HCLGE_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGE_RSS_KEY_SIZE ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_rss_algo_key (struct hclge_dev*,scalar_t__,scalar_t__ const*) ; 
 int hclge_set_rss_indir_table (struct hclge_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_rss(struct hnae3_handle *handle, const u32 *indir,
			 const  u8 *key, const  u8 hfunc)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u8 hash_algo;
	int ret, i;

	/* Set the RSS Hash Key if specififed by the user */
	if (key) {

		if (hfunc == ETH_RSS_HASH_TOP ||
		    hfunc == ETH_RSS_HASH_NO_CHANGE)
			hash_algo = HCLGE_RSS_HASH_ALGO_TOEPLITZ;
		else
			return -EINVAL;
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