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
struct net_device {int dummy; } ;
struct hinic_dev {int flags; int /*<<< orphan*/  rss_tmpl_idx; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_RSS_HASH_TOP ; 
 scalar_t__ ETH_RSS_HASH_XOR ; 
 int HINIC_RSS_ENABLE ; 
 int hinic_rss_get_hash_engine (struct hinic_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int hinic_rss_get_indir_tbl (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hinic_rss_get_template_tbl (struct hinic_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hinic_get_rxfh(struct net_device *netdev,
			  u32 *indir, u8 *key, u8 *hfunc)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	u8 hash_engine_type = 0;
	int err = 0;

	if (!(nic_dev->flags & HINIC_RSS_ENABLE))
		return -EOPNOTSUPP;

	if (hfunc) {
		err = hinic_rss_get_hash_engine(nic_dev,
						nic_dev->rss_tmpl_idx,
						&hash_engine_type);
		if (err)
			return -EFAULT;

		*hfunc = hash_engine_type ? ETH_RSS_HASH_TOP : ETH_RSS_HASH_XOR;
	}

	if (indir) {
		err = hinic_rss_get_indir_tbl(nic_dev,
					      nic_dev->rss_tmpl_idx, indir);
		if (err)
			return -EFAULT;
	}

	if (key)
		err = hinic_rss_get_template_tbl(nic_dev,
						 nic_dev->rss_tmpl_idx, key);

	return err;
}