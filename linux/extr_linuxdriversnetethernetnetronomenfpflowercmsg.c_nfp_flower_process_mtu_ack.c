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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ requested_val; scalar_t__ portnum; int ack; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_q; } ;
struct nfp_flower_priv {TYPE_1__ mtu_conf; } ;
struct nfp_flower_cmsg_portmod {int info; int /*<<< orphan*/  mtu; int /*<<< orphan*/  portnum; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int NFP_FLOWER_CMSG_PORTMOD_MTU_CHANGE_ONLY ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct nfp_flower_cmsg_portmod* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
nfp_flower_process_mtu_ack(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_flower_priv *app_priv = app->priv;
	struct nfp_flower_cmsg_portmod *msg;

	msg = nfp_flower_cmsg_get_data(skb);

	if (!(msg->info & NFP_FLOWER_CMSG_PORTMOD_MTU_CHANGE_ONLY))
		return false;

	spin_lock_bh(&app_priv->mtu_conf.lock);
	if (!app_priv->mtu_conf.requested_val ||
	    app_priv->mtu_conf.portnum != be32_to_cpu(msg->portnum) ||
	    be16_to_cpu(msg->mtu) != app_priv->mtu_conf.requested_val) {
		/* Not an ack for requested MTU change. */
		spin_unlock_bh(&app_priv->mtu_conf.lock);
		return false;
	}

	app_priv->mtu_conf.ack = true;
	app_priv->mtu_conf.requested_val = 0;
	wake_up(&app_priv->mtu_conf.wait_q);
	spin_unlock_bh(&app_priv->mtu_conf.lock);

	return true;
}