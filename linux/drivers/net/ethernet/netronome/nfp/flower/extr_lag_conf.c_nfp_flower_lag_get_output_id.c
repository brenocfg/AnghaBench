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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct nfp_flower_priv {TYPE_1__ nfp_lag; } ;
struct nfp_fl_lag_group {int group_id; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfp_fl_lag_group* nfp_fl_lag_find_group_for_master_with_lag (TYPE_1__*,struct net_device*) ; 

int nfp_flower_lag_get_output_id(struct nfp_app *app, struct net_device *master)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_lag_group *group = NULL;
	int group_id = -ENOENT;

	mutex_lock(&priv->nfp_lag.lock);
	group = nfp_fl_lag_find_group_for_master_with_lag(&priv->nfp_lag,
							  master);
	if (group)
		group_id = group->group_id;
	mutex_unlock(&priv->nfp_lag.lock);

	return group_id;
}