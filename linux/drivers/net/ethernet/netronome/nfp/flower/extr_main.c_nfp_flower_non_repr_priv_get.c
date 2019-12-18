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
struct nfp_flower_priv {int /*<<< orphan*/  non_repr_priv; } ;
struct nfp_flower_non_repr_priv {int /*<<< orphan*/  list; struct net_device* netdev; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __nfp_flower_non_repr_priv_get (struct nfp_flower_non_repr_priv*) ; 
 struct nfp_flower_non_repr_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfp_flower_non_repr_priv* nfp_flower_non_repr_priv_lookup (struct nfp_app*,struct net_device*) ; 

struct nfp_flower_non_repr_priv *
nfp_flower_non_repr_priv_get(struct nfp_app *app, struct net_device *netdev)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_flower_non_repr_priv *entry;

	entry = nfp_flower_non_repr_priv_lookup(app, netdev);
	if (entry)
		goto inc_ref;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return NULL;

	entry->netdev = netdev;
	list_add(&entry->list, &priv->non_repr_priv);

inc_ref:
	__nfp_flower_non_repr_priv_get(entry);
	return entry;
}