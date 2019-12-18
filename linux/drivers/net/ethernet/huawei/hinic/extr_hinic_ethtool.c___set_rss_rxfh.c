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
struct hinic_dev {int /*<<< orphan*/  rss_tmpl_idx; void* rss_hkey_user; void* rss_indir_user; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HINIC_RSS_INDIR_SIZE ; 
 int HINIC_RSS_KEY_SIZE ; 
 int hinic_rss_set_indir_tbl (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int hinic_rss_set_template_tbl (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int __set_rss_rxfh(struct net_device *netdev,
			  const u32 *indir, const u8 *key)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	int err;

	if (indir) {
		if (!nic_dev->rss_indir_user) {
			nic_dev->rss_indir_user =
				kzalloc(sizeof(u32) * HINIC_RSS_INDIR_SIZE,
					GFP_KERNEL);
			if (!nic_dev->rss_indir_user)
				return -ENOMEM;
		}

		memcpy(nic_dev->rss_indir_user, indir,
		       sizeof(u32) * HINIC_RSS_INDIR_SIZE);

		err = hinic_rss_set_indir_tbl(nic_dev,
					      nic_dev->rss_tmpl_idx, indir);
		if (err)
			return -EFAULT;
	}

	if (key) {
		if (!nic_dev->rss_hkey_user) {
			nic_dev->rss_hkey_user =
				kzalloc(HINIC_RSS_KEY_SIZE * 2, GFP_KERNEL);

			if (!nic_dev->rss_hkey_user)
				return -ENOMEM;
		}

		memcpy(nic_dev->rss_hkey_user, key, HINIC_RSS_KEY_SIZE);

		err = hinic_rss_set_template_tbl(nic_dev,
						 nic_dev->rss_tmpl_idx, key);
		if (err)
			return -EFAULT;
	}

	return 0;
}