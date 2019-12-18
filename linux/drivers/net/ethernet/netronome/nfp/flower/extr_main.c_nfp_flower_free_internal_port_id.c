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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  port_ids; } ;
struct nfp_flower_priv {TYPE_1__ internal_ports; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int nfp_flower_lookup_internal_port_id (struct nfp_flower_priv*,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_flower_free_internal_port_id(struct nfp_app *app, struct net_device *netdev)
{
	struct nfp_flower_priv *priv = app->priv;
	int id;

	id = nfp_flower_lookup_internal_port_id(priv, netdev);
	if (!id)
		return;

	spin_lock_bh(&priv->internal_ports.lock);
	idr_remove(&priv->internal_ports.port_ids, id);
	spin_unlock_bh(&priv->internal_ports.lock);
}