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
struct nfp_flower_priv {int /*<<< orphan*/  flow_table; } ;
struct nfp_fl_payload {int dummy; } ;
struct nfp_fl_flow_table_cmp_arg {unsigned long cookie; struct net_device* netdev; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_flower_table_params ; 
 struct nfp_fl_payload* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct nfp_fl_flow_table_cmp_arg*,int /*<<< orphan*/ ) ; 

struct nfp_fl_payload *
nfp_flower_search_fl_table(struct nfp_app *app, unsigned long tc_flower_cookie,
			   struct net_device *netdev)
{
	struct nfp_fl_flow_table_cmp_arg flower_cmp_arg;
	struct nfp_flower_priv *priv = app->priv;

	flower_cmp_arg.netdev = netdev;
	flower_cmp_arg.cookie = tc_flower_cookie;

	return rhashtable_lookup_fast(&priv->flow_table, &flower_cmp_arg,
				      nfp_flower_table_params);
}