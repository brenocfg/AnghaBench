#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct nfp_flower_priv {int /*<<< orphan*/  stats_ctx_table; TYPE_1__* stats; int /*<<< orphan*/  flower_version; } ;
struct nfp_fl_stats_ctx_to_flow {size_t stats_cxt; int /*<<< orphan*/  ht_node; struct nfp_fl_payload* flow; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask_len; void* flow_version; int /*<<< orphan*/  flags; void* host_cookie; int /*<<< orphan*/  host_ctx_id; } ;
struct nfp_fl_payload {TYPE_2__ meta; int /*<<< orphan*/  mask_data; scalar_t__* unmasked_data; struct net_device* ingress_dev; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; scalar_t__ bytes; scalar_t__ pkts; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFP_FL_MASK_ID_LOCATION ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (size_t) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct nfp_fl_stats_ctx_to_flow*) ; 
 struct nfp_fl_stats_ctx_to_flow* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_check_mask_add (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nfp_check_mask_remove (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*) ; 
 int nfp_get_stats_entry (struct nfp_app*,size_t*) ; 
 scalar_t__ nfp_release_stats_entry (struct nfp_app*,size_t) ; 
 scalar_t__ rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_ctx_table_params ; 

int nfp_compile_flow_metadata(struct nfp_app *app,
			      struct flow_cls_offload *flow,
			      struct nfp_fl_payload *nfp_flow,
			      struct net_device *netdev,
			      struct netlink_ext_ack *extack)
{
	struct nfp_fl_stats_ctx_to_flow *ctx_entry;
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_payload *check_entry;
	u8 new_mask_id;
	u32 stats_cxt;
	int err;

	err = nfp_get_stats_entry(app, &stats_cxt);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot allocate new stats context");
		return err;
	}

	nfp_flow->meta.host_ctx_id = cpu_to_be32(stats_cxt);
	nfp_flow->meta.host_cookie = cpu_to_be64(flow->cookie);
	nfp_flow->ingress_dev = netdev;

	ctx_entry = kzalloc(sizeof(*ctx_entry), GFP_KERNEL);
	if (!ctx_entry) {
		err = -ENOMEM;
		goto err_release_stats;
	}

	ctx_entry->stats_cxt = stats_cxt;
	ctx_entry->flow = nfp_flow;

	if (rhashtable_insert_fast(&priv->stats_ctx_table, &ctx_entry->ht_node,
				   stats_ctx_table_params)) {
		err = -ENOMEM;
		goto err_free_ctx_entry;
	}

	new_mask_id = 0;
	if (!nfp_check_mask_add(app, nfp_flow->mask_data,
				nfp_flow->meta.mask_len,
				&nfp_flow->meta.flags, &new_mask_id)) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot allocate a new mask id");
		if (nfp_release_stats_entry(app, stats_cxt)) {
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release stats context");
			err = -EINVAL;
			goto err_remove_rhash;
		}
		err = -ENOENT;
		goto err_remove_rhash;
	}

	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;

	/* Update flow payload with mask ids. */
	nfp_flow->unmasked_data[NFP_FL_MASK_ID_LOCATION] = new_mask_id;
	priv->stats[stats_cxt].pkts = 0;
	priv->stats[stats_cxt].bytes = 0;
	priv->stats[stats_cxt].used = jiffies;

	check_entry = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	if (check_entry) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot offload duplicate flow entry");
		if (nfp_release_stats_entry(app, stats_cxt)) {
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release stats context");
			err = -EINVAL;
			goto err_remove_mask;
		}

		if (!nfp_check_mask_remove(app, nfp_flow->mask_data,
					   nfp_flow->meta.mask_len,
					   NULL, &new_mask_id)) {
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release mask id");
			err = -EINVAL;
			goto err_remove_mask;
		}

		err = -EEXIST;
		goto err_remove_mask;
	}

	return 0;

err_remove_mask:
	nfp_check_mask_remove(app, nfp_flow->mask_data, nfp_flow->meta.mask_len,
			      NULL, &new_mask_id);
err_remove_rhash:
	WARN_ON_ONCE(rhashtable_remove_fast(&priv->stats_ctx_table,
					    &ctx_entry->ht_node,
					    stats_ctx_table_params));
err_free_ctx_entry:
	kfree(ctx_entry);
err_release_stats:
	nfp_release_stats_entry(app, stats_cxt);

	return err;
}