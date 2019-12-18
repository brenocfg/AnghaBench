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
struct net_device {int dummy; } ;
struct bnxt_vnic_info {scalar_t__ rss_hash_key; int /*<<< orphan*/ * rss_table; } ;
struct bnxt {struct bnxt_vnic_info* vnic_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int HW_HASH_INDEX_SIZE ; 
 int /*<<< orphan*/  HW_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_rxfh(struct net_device *dev, u32 *indir, u8 *key,
			 u8 *hfunc)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_vnic_info *vnic;
	int i = 0;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	if (!bp->vnic_info)
		return 0;

	vnic = &bp->vnic_info[0];
	if (indir && vnic->rss_table) {
		for (i = 0; i < HW_HASH_INDEX_SIZE; i++)
			indir[i] = le16_to_cpu(vnic->rss_table[i]);
	}

	if (key && vnic->rss_hash_key)
		memcpy(key, vnic->rss_hash_key, HW_HASH_KEY_SIZE);

	return 0;
}