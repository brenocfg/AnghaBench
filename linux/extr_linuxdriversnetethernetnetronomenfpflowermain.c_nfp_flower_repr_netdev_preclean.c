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
struct nfp_repr {int dummy; } ;
struct nfp_flower_priv {int /*<<< orphan*/  reify_replies; } ;
struct nfp_app {int /*<<< orphan*/  cpp; struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int nfp_flower_cmsg_portreify (struct nfp_repr*,int) ; 
 int /*<<< orphan*/  nfp_flower_wait_repr_reify (struct nfp_app*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
nfp_flower_repr_netdev_preclean(struct nfp_app *app, struct net_device *netdev)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	struct nfp_flower_priv *priv = app->priv;
	atomic_t *replies = &priv->reify_replies;
	int err;

	atomic_set(replies, 0);
	err = nfp_flower_cmsg_portreify(repr, false);
	if (err) {
		nfp_warn(app->cpp, "Failed to notify firmware about repr destruction\n");
		return;
	}

	nfp_flower_wait_repr_reify(app, replies, 1);
}