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
struct wcn36xx {int /*<<< orphan*/  hal_buf; int /*<<< orphan*/  dxe_lock; int /*<<< orphan*/  vif_list; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  WCN36XX_HAL_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_debugfs_init (struct wcn36xx*) ; 
 int wcn36xx_dxe_alloc_ctl_blks (struct wcn36xx*) ; 
 int wcn36xx_dxe_allocate_mem_pools (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_ctl_blks (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_mem_pools (struct wcn36xx*) ; 
 int wcn36xx_dxe_init (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int /*<<< orphan*/  wcn36xx_feat_caps_info (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_is_fw_version (struct wcn36xx*,int,int,int,int) ; 
 int /*<<< orphan*/  wcn36xx_smd_close (struct wcn36xx*) ; 
 int wcn36xx_smd_feature_caps_exchange (struct wcn36xx*) ; 
 int wcn36xx_smd_load_nv (struct wcn36xx*) ; 
 int wcn36xx_smd_open (struct wcn36xx*) ; 
 int wcn36xx_smd_start (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_smd_stop (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

__attribute__((used)) static int wcn36xx_start(struct ieee80211_hw *hw)
{
	struct wcn36xx *wcn = hw->priv;
	int ret;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac start\n");

	/* SMD initialization */
	ret = wcn36xx_smd_open(wcn);
	if (ret) {
		wcn36xx_err("Failed to open smd channel: %d\n", ret);
		goto out_err;
	}

	/* Allocate memory pools for Mgmt BD headers and Data BD headers */
	ret = wcn36xx_dxe_allocate_mem_pools(wcn);
	if (ret) {
		wcn36xx_err("Failed to alloc DXE mempool: %d\n", ret);
		goto out_smd_close;
	}

	ret = wcn36xx_dxe_alloc_ctl_blks(wcn);
	if (ret) {
		wcn36xx_err("Failed to alloc DXE ctl blocks: %d\n", ret);
		goto out_free_dxe_pool;
	}

	wcn->hal_buf = kmalloc(WCN36XX_HAL_BUF_SIZE, GFP_KERNEL);
	if (!wcn->hal_buf) {
		wcn36xx_err("Failed to allocate smd buf\n");
		ret = -ENOMEM;
		goto out_free_dxe_ctl;
	}

	ret = wcn36xx_smd_load_nv(wcn);
	if (ret) {
		wcn36xx_err("Failed to push NV to chip\n");
		goto out_free_smd_buf;
	}

	ret = wcn36xx_smd_start(wcn);
	if (ret) {
		wcn36xx_err("Failed to start chip\n");
		goto out_free_smd_buf;
	}

	if (!wcn36xx_is_fw_version(wcn, 1, 2, 2, 24)) {
		ret = wcn36xx_smd_feature_caps_exchange(wcn);
		if (ret)
			wcn36xx_warn("Exchange feature caps failed\n");
		else
			wcn36xx_feat_caps_info(wcn);
	}

	/* DMA channel initialization */
	ret = wcn36xx_dxe_init(wcn);
	if (ret) {
		wcn36xx_err("DXE init failed\n");
		goto out_smd_stop;
	}

	wcn36xx_debugfs_init(wcn);

	INIT_LIST_HEAD(&wcn->vif_list);
	spin_lock_init(&wcn->dxe_lock);

	return 0;

out_smd_stop:
	wcn36xx_smd_stop(wcn);
out_free_smd_buf:
	kfree(wcn->hal_buf);
out_free_dxe_ctl:
	wcn36xx_dxe_free_ctl_blks(wcn);
out_free_dxe_pool:
	wcn36xx_dxe_free_mem_pools(wcn);
out_smd_close:
	wcn36xx_smd_close(wcn);
out_err:
	return ret;
}