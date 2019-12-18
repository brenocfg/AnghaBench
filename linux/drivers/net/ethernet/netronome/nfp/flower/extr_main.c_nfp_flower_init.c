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
typedef  scalar_t__ u64 ;
struct nfp_pf {int /*<<< orphan*/  rtbl; int /*<<< orphan*/  vf_cfg_bar; int /*<<< orphan*/  mac_stats_bar; int /*<<< orphan*/  eth_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_q; } ;
struct nfp_flower_priv {int flower_ext_feats; int /*<<< orphan*/  nfp_lag; scalar_t__ pre_tun_rule_cnt; int /*<<< orphan*/  non_repr_priv; int /*<<< orphan*/  indr_block_cb_priv; TYPE_1__ mtu_conf; int /*<<< orphan*/  reify_wait_queue; int /*<<< orphan*/  cmsg_work; int /*<<< orphan*/  cmsg_skbs_low; int /*<<< orphan*/  cmsg_skbs_high; struct nfp_app* app; int /*<<< orphan*/  stats_ring_size; scalar_t__ active_mem_unit; scalar_t__ total_mem_units; } ;
struct nfp_app {struct nfp_flower_priv* priv; int /*<<< orphan*/  cpp; struct nfp_pf* pf; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIELD_FIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NFP_FLOWER_ALLOWED_VER ; 
 int NFP_FL_FEATS_FLOW_MERGE ; 
 int NFP_FL_FEATS_FLOW_MOD ; 
 int NFP_FL_FEATS_LAG ; 
 int NFP_FL_FEATS_VF_RLIM ; 
 int /*<<< orphan*/  NFP_FL_STAT_ID_MU_NUM ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_process_rx ; 
 int /*<<< orphan*/  nfp_flower_internal_port_init (struct nfp_flower_priv*) ; 
 int /*<<< orphan*/  nfp_flower_lag_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_lag_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_flower_metadata_cleanup (struct nfp_app*) ; 
 int nfp_flower_metadata_init (struct nfp_app*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfp_flower_qos_init (struct nfp_app*) ; 
 scalar_t__ nfp_rtsym_read_le (int /*<<< orphan*/ ,char*,int*) ; 
 int nfp_rtsym_write_le (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  roundup_pow_of_two (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct nfp_flower_priv*) ; 
 struct nfp_flower_priv* vzalloc (int) ; 

__attribute__((used)) static int nfp_flower_init(struct nfp_app *app)
{
	u64 version, features, ctx_count, num_mems;
	const struct nfp_pf *pf = app->pf;
	struct nfp_flower_priv *app_priv;
	int err;

	if (!pf->eth_tbl) {
		nfp_warn(app->cpp, "FlowerNIC requires eth table\n");
		return -EINVAL;
	}

	if (!pf->mac_stats_bar) {
		nfp_warn(app->cpp, "FlowerNIC requires mac_stats BAR\n");
		return -EINVAL;
	}

	if (!pf->vf_cfg_bar) {
		nfp_warn(app->cpp, "FlowerNIC requires vf_cfg BAR\n");
		return -EINVAL;
	}

	version = nfp_rtsym_read_le(app->pf->rtbl, "hw_flower_version", &err);
	if (err) {
		nfp_warn(app->cpp, "FlowerNIC requires hw_flower_version memory symbol\n");
		return err;
	}

	num_mems = nfp_rtsym_read_le(app->pf->rtbl, "CONFIG_FC_HOST_CTX_SPLIT",
				     &err);
	if (err) {
		nfp_warn(app->cpp,
			 "FlowerNIC: unsupported host context memory: %d\n",
			 err);
		err = 0;
		num_mems = 1;
	}

	if (!FIELD_FIT(NFP_FL_STAT_ID_MU_NUM, num_mems) || !num_mems) {
		nfp_warn(app->cpp,
			 "FlowerNIC: invalid host context memory: %llu\n",
			 num_mems);
		return -EINVAL;
	}

	ctx_count = nfp_rtsym_read_le(app->pf->rtbl, "CONFIG_FC_HOST_CTX_COUNT",
				      &err);
	if (err) {
		nfp_warn(app->cpp,
			 "FlowerNIC: unsupported host context count: %d\n",
			 err);
		err = 0;
		ctx_count = BIT(17);
	}

	/* We need to ensure hardware has enough flower capabilities. */
	if (version != NFP_FLOWER_ALLOWED_VER) {
		nfp_warn(app->cpp, "FlowerNIC: unsupported firmware version\n");
		return -EINVAL;
	}

	app_priv = vzalloc(sizeof(struct nfp_flower_priv));
	if (!app_priv)
		return -ENOMEM;

	app_priv->total_mem_units = num_mems;
	app_priv->active_mem_unit = 0;
	app_priv->stats_ring_size = roundup_pow_of_two(ctx_count);
	app->priv = app_priv;
	app_priv->app = app;
	skb_queue_head_init(&app_priv->cmsg_skbs_high);
	skb_queue_head_init(&app_priv->cmsg_skbs_low);
	INIT_WORK(&app_priv->cmsg_work, nfp_flower_cmsg_process_rx);
	init_waitqueue_head(&app_priv->reify_wait_queue);

	init_waitqueue_head(&app_priv->mtu_conf.wait_q);
	spin_lock_init(&app_priv->mtu_conf.lock);

	err = nfp_flower_metadata_init(app, ctx_count, num_mems);
	if (err)
		goto err_free_app_priv;

	/* Extract the extra features supported by the firmware. */
	features = nfp_rtsym_read_le(app->pf->rtbl,
				     "_abi_flower_extra_features", &err);
	if (err)
		app_priv->flower_ext_feats = 0;
	else
		app_priv->flower_ext_feats = features;

	/* Tell the firmware that the driver supports lag. */
	err = nfp_rtsym_write_le(app->pf->rtbl,
				 "_abi_flower_balance_sync_enable", 1);
	if (!err) {
		app_priv->flower_ext_feats |= NFP_FL_FEATS_LAG;
		nfp_flower_lag_init(&app_priv->nfp_lag);
	} else if (err == -ENOENT) {
		nfp_warn(app->cpp, "LAG not supported by FW.\n");
	} else {
		goto err_cleanup_metadata;
	}

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_FLOW_MOD) {
		/* Tell the firmware that the driver supports flow merging. */
		err = nfp_rtsym_write_le(app->pf->rtbl,
					 "_abi_flower_merge_hint_enable", 1);
		if (!err) {
			app_priv->flower_ext_feats |= NFP_FL_FEATS_FLOW_MERGE;
			nfp_flower_internal_port_init(app_priv);
		} else if (err == -ENOENT) {
			nfp_warn(app->cpp, "Flow merge not supported by FW.\n");
		} else {
			goto err_lag_clean;
		}
	} else {
		nfp_warn(app->cpp, "Flow mod/merge not supported by FW.\n");
	}

	if (app_priv->flower_ext_feats & NFP_FL_FEATS_VF_RLIM)
		nfp_flower_qos_init(app);

	INIT_LIST_HEAD(&app_priv->indr_block_cb_priv);
	INIT_LIST_HEAD(&app_priv->non_repr_priv);
	app_priv->pre_tun_rule_cnt = 0;

	return 0;

err_lag_clean:
	if (app_priv->flower_ext_feats & NFP_FL_FEATS_LAG)
		nfp_flower_lag_cleanup(&app_priv->nfp_lag);
err_cleanup_metadata:
	nfp_flower_metadata_cleanup(app);
err_free_app_priv:
	vfree(app->priv);
	return err;
}