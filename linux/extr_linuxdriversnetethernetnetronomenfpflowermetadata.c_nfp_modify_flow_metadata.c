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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_flower_priv {int /*<<< orphan*/  flower_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_ctx_id; int /*<<< orphan*/  flow_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask_len; } ;
struct nfp_fl_payload {TYPE_1__ meta; int /*<<< orphan*/ * unmasked_data; int /*<<< orphan*/  mask_data; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 size_t NFP_FL_MASK_ID_LOCATION ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_check_mask_remove (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfp_release_stats_entry (struct nfp_app*,int /*<<< orphan*/ ) ; 

int nfp_modify_flow_metadata(struct nfp_app *app,
			     struct nfp_fl_payload *nfp_flow)
{
	struct nfp_flower_priv *priv = app->priv;
	u8 new_mask_id = 0;
	u32 temp_ctx_id;

	nfp_check_mask_remove(app, nfp_flow->mask_data,
			      nfp_flow->meta.mask_len, &nfp_flow->meta.flags,
			      &new_mask_id);

	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;

	/* Update flow payload with mask ids. */
	nfp_flow->unmasked_data[NFP_FL_MASK_ID_LOCATION] = new_mask_id;

	/* Release the stats ctx id. */
	temp_ctx_id = be32_to_cpu(nfp_flow->meta.host_ctx_id);

	return nfp_release_stats_entry(app, temp_ctx_id);
}