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
struct TYPE_2__ {int batch_ver; int /*<<< orphan*/  lock; } ;
struct nfp_flower_priv {TYPE_1__ nfp_lag; } ;
struct nfp_fl_pre_lag {int /*<<< orphan*/  instance; int /*<<< orphan*/  lag_version; int /*<<< orphan*/  group_id; } ;
struct nfp_fl_lag_group {int /*<<< orphan*/  group_inst; int /*<<< orphan*/  group_id; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int NFP_FL_PRE_LAG_VER_OFF ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfp_fl_lag_group* nfp_fl_lag_find_group_for_master_with_lag (TYPE_1__*,struct net_device*) ; 

int nfp_flower_lag_populate_pre_action(struct nfp_app *app,
				       struct net_device *master,
				       struct nfp_fl_pre_lag *pre_act,
				       struct netlink_ext_ack *extack)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_lag_group *group = NULL;
	__be32 temp_vers;

	mutex_lock(&priv->nfp_lag.lock);
	group = nfp_fl_lag_find_group_for_master_with_lag(&priv->nfp_lag,
							  master);
	if (!group) {
		mutex_unlock(&priv->nfp_lag.lock);
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: group does not exist for LAG action");
		return -ENOENT;
	}

	pre_act->group_id = cpu_to_be16(group->group_id);
	temp_vers = cpu_to_be32(priv->nfp_lag.batch_ver <<
				NFP_FL_PRE_LAG_VER_OFF);
	memcpy(pre_act->lag_version, &temp_vers, 3);
	pre_act->instance = group->group_inst;
	mutex_unlock(&priv->nfp_lag.lock);

	return 0;
}