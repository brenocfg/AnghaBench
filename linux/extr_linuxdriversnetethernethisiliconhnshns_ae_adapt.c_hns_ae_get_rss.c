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
struct hns_ppe_cb {int /*<<< orphan*/  rss_indir_table; int /*<<< orphan*/  rss_key; } ;
struct hnae_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int HNS_PPEV2_RSS_IND_TBL_SIZE ; 
 int HNS_PPEV2_RSS_KEY_SIZE ; 
 struct hns_ppe_cb* hns_get_ppe_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_ae_get_rss(struct hnae_handle *handle, u32 *indir, u8 *key,
			  u8 *hfunc)
{
	struct hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	/* currently we support only one type of hash function i.e. Toep hash */
	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	/* get the RSS Key required by the user */
	if (key)
		memcpy(key, ppe_cb->rss_key, HNS_PPEV2_RSS_KEY_SIZE);

	/* update the current hash->queue mappings from the shadow RSS table */
	if (indir)
		memcpy(indir, ppe_cb->rss_indir_table,
		       HNS_PPEV2_RSS_IND_TBL_SIZE  * sizeof(*indir));

	return 0;
}