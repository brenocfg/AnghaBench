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
typedef  int /*<<< orphan*/  u32 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  cookie; } ;
struct nfp_flower_priv {int /*<<< orphan*/  flower_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask_len; void* flow_version; int /*<<< orphan*/  flags; void* host_cookie; int /*<<< orphan*/  host_ctx_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; scalar_t__ bytes; scalar_t__ pkts; } ;
struct nfp_fl_payload {TYPE_2__ meta; int /*<<< orphan*/  mask_data; TYPE_1__ stats; scalar_t__* unmasked_data; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 size_t NFP_FL_MASK_ID_LOCATION ; 
 int /*<<< orphan*/  NFP_FL_STATS_CTX_DONT_CARE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfp_check_mask_add (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nfp_check_mask_remove (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_get_stats_entry (struct nfp_app*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfp_release_stats_entry (struct nfp_app*,int /*<<< orphan*/ ) ; 

int nfp_compile_flow_metadata(struct nfp_app *app,
			      struct tc_cls_flower_offload *flow,
			      struct nfp_fl_payload *nfp_flow,
			      struct net_device *netdev)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_payload *check_entry;
	u8 new_mask_id;
	u32 stats_cxt;

	if (nfp_get_stats_entry(app, &stats_cxt))
		return -ENOENT;

	nfp_flow->meta.host_ctx_id = cpu_to_be32(stats_cxt);
	nfp_flow->meta.host_cookie = cpu_to_be64(flow->cookie);

	new_mask_id = 0;
	if (!nfp_check_mask_add(app, nfp_flow->mask_data,
				nfp_flow->meta.mask_len,
				&nfp_flow->meta.flags, &new_mask_id)) {
		if (nfp_release_stats_entry(app, stats_cxt))
			return -EINVAL;
		return -ENOENT;
	}

	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;

	/* Update flow payload with mask ids. */
	nfp_flow->unmasked_data[NFP_FL_MASK_ID_LOCATION] = new_mask_id;
	nfp_flow->stats.pkts = 0;
	nfp_flow->stats.bytes = 0;
	nfp_flow->stats.used = jiffies;

	check_entry = nfp_flower_search_fl_table(app, flow->cookie, netdev,
						 NFP_FL_STATS_CTX_DONT_CARE);
	if (check_entry) {
		if (nfp_release_stats_entry(app, stats_cxt))
			return -EINVAL;

		if (!nfp_check_mask_remove(app, nfp_flow->mask_data,
					   nfp_flow->meta.mask_len,
					   NULL, &new_mask_id))
			return -EINVAL;

		return -EEXIST;
	}

	return 0;
}