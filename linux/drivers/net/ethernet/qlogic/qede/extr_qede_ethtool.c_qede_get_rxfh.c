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
struct qede_dev {int /*<<< orphan*/  rss_key; int /*<<< orphan*/ * rss_ind_table; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int QED_RSS_IND_TABLE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_get_rxfh_key_size (struct net_device*) ; 

__attribute__((used)) static int qede_get_rxfh(struct net_device *dev, u32 *indir, u8 *key, u8 *hfunc)
{
	struct qede_dev *edev = netdev_priv(dev);
	int i;

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	if (!indir)
		return 0;

	for (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++)
		indir[i] = edev->rss_ind_table[i];

	if (key)
		memcpy(key, edev->rss_key, qede_get_rxfh_key_size(dev));

	return 0;
}