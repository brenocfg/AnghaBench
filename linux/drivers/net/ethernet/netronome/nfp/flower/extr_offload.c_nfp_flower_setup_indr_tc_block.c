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
struct nfp_flower_priv {int /*<<< orphan*/  indr_block_cb_priv; } ;
struct nfp_flower_indr_block_cb_priv {int /*<<< orphan*/  list; struct nfp_app* app; struct net_device* netdev; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;
struct flow_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ ,struct nfp_flower_indr_block_cb_priv*,struct nfp_flower_indr_block_cb_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_block_cb_is_busy (int /*<<< orphan*/ ,struct nfp_flower_indr_block_cb_priv*,int /*<<< orphan*/ *) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_flower_indr_block_cb_priv*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  kfree (struct nfp_flower_indr_block_cb_priv*) ; 
 struct nfp_flower_indr_block_cb_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_block_cb_list ; 
 struct nfp_flower_indr_block_cb_priv* nfp_flower_indr_block_cb_priv_lookup (struct nfp_app*,struct net_device*) ; 
 scalar_t__ nfp_flower_internal_port_can_offload (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_setup_indr_block_cb ; 
 int /*<<< orphan*/  nfp_flower_setup_indr_tc_release ; 

__attribute__((used)) static int
nfp_flower_setup_indr_tc_block(struct net_device *netdev, struct nfp_app *app,
			       struct flow_block_offload *f)
{
	struct nfp_flower_indr_block_cb_priv *cb_priv;
	struct nfp_flower_priv *priv = app->priv;
	struct flow_block_cb *block_cb;

	if ((f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS &&
	     !nfp_flower_internal_port_can_offload(app, netdev)) ||
	    (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS &&
	     nfp_flower_internal_port_can_offload(app, netdev)))
		return -EOPNOTSUPP;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		cb_priv = nfp_flower_indr_block_cb_priv_lookup(app, netdev);
		if (cb_priv &&
		    flow_block_cb_is_busy(nfp_flower_setup_indr_block_cb,
					  cb_priv,
					  &nfp_block_cb_list))
			return -EBUSY;

		cb_priv = kmalloc(sizeof(*cb_priv), GFP_KERNEL);
		if (!cb_priv)
			return -ENOMEM;

		cb_priv->netdev = netdev;
		cb_priv->app = app;
		list_add(&cb_priv->list, &priv->indr_block_cb_priv);

		block_cb = flow_block_cb_alloc(nfp_flower_setup_indr_block_cb,
					       cb_priv, cb_priv,
					       nfp_flower_setup_indr_tc_release);
		if (IS_ERR(block_cb)) {
			list_del(&cb_priv->list);
			kfree(cb_priv);
			return PTR_ERR(block_cb);
		}

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &nfp_block_cb_list);
		return 0;
	case FLOW_BLOCK_UNBIND:
		cb_priv = nfp_flower_indr_block_cb_priv_lookup(app, netdev);
		if (!cb_priv)
			return -ENOENT;

		block_cb = flow_block_cb_lookup(f->block,
						nfp_flower_setup_indr_block_cb,
						cb_priv);
		if (!block_cb)
			return -ENOENT;

		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}