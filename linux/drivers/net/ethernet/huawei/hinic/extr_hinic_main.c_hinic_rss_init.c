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
struct hinic_dev {int /*<<< orphan*/  rss_hash_engine; int /*<<< orphan*/  rss_type; int /*<<< orphan*/  num_rss; int /*<<< orphan*/  rss_tmpl_idx; } ;
typedef  int /*<<< orphan*/  default_rss_key ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HINIC_RSS_INDIR_SIZE ; 
 int HINIC_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 int hinic_rss_cfg (struct hinic_dev*,int,int /*<<< orphan*/ ) ; 
 int hinic_rss_set_hash_engine (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hinic_rss_set_indir_tbl (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hinic_rss_set_template_tbl (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hinic_set_rss_type (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hinic_rss_init(struct hinic_dev *nic_dev)
{
	u8 default_rss_key[HINIC_RSS_KEY_SIZE];
	u8 tmpl_idx = nic_dev->rss_tmpl_idx;
	u32 *indir_tbl;
	int err, i;

	indir_tbl = kcalloc(HINIC_RSS_INDIR_SIZE, sizeof(u32), GFP_KERNEL);
	if (!indir_tbl)
		return -ENOMEM;

	netdev_rss_key_fill(default_rss_key, sizeof(default_rss_key));
	for (i = 0; i < HINIC_RSS_INDIR_SIZE; i++)
		indir_tbl[i] = ethtool_rxfh_indir_default(i, nic_dev->num_rss);

	err = hinic_rss_set_template_tbl(nic_dev, tmpl_idx, default_rss_key);
	if (err)
		goto out;

	err = hinic_rss_set_indir_tbl(nic_dev, tmpl_idx, indir_tbl);
	if (err)
		goto out;

	err = hinic_set_rss_type(nic_dev, tmpl_idx, nic_dev->rss_type);
	if (err)
		goto out;

	err = hinic_rss_set_hash_engine(nic_dev, tmpl_idx,
					nic_dev->rss_hash_engine);
	if (err)
		goto out;

	err = hinic_rss_cfg(nic_dev, 1, tmpl_idx);
	if (err)
		goto out;

out:
	kfree(indir_tbl);
	return err;
}