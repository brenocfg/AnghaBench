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
struct sk_buff {int dummy; } ;
struct nfp_flower_priv {int /*<<< orphan*/  reify_wait_queue; int /*<<< orphan*/  reify_replies; } ;
struct nfp_flower_cmsg_portreify {int /*<<< orphan*/  portnum; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_app_dev_get (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfp_flower_cmsg_portreify* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_flower_cmsg_portreify_rx(struct nfp_app *app, struct sk_buff *skb)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_flower_cmsg_portreify *msg;
	bool exists;

	msg = nfp_flower_cmsg_get_data(skb);

	rcu_read_lock();
	exists = !!nfp_app_dev_get(app, be32_to_cpu(msg->portnum), NULL);
	rcu_read_unlock();
	if (!exists) {
		nfp_flower_cmsg_warn(app, "ctrl msg for unknown port 0x%08x\n",
				     be32_to_cpu(msg->portnum));
		return;
	}

	atomic_inc(&priv->reify_replies);
	wake_up(&priv->reify_wait_queue);
}