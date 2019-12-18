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
struct nfp_flower_non_repr_priv {int dummy; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfp_flower_non_repr_priv_put (struct nfp_flower_non_repr_priv*) ; 
 struct nfp_flower_non_repr_priv* nfp_flower_non_repr_priv_lookup (struct nfp_app*,struct net_device*) ; 

void
nfp_flower_non_repr_priv_put(struct nfp_app *app, struct net_device *netdev)
{
	struct nfp_flower_non_repr_priv *entry;

	entry = nfp_flower_non_repr_priv_lookup(app, netdev);
	if (!entry)
		return;

	__nfp_flower_non_repr_priv_put(entry);
}