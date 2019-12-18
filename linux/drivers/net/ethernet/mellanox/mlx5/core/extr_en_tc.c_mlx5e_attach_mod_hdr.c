#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mod_hdr_tbl {int /*<<< orphan*/  lock; int /*<<< orphan*/  hlist; } ;
struct mod_hdr_key {int num_actions; int /*<<< orphan*/  actions; } ;
struct mlx5e_tc_flow_parse_attr {int num_mod_hdr_actions; int /*<<< orphan*/  mod_hdr_actions; } ;
struct mlx5e_tc_flow {TYPE_3__* nic_attr; TYPE_2__* esw_attr; int /*<<< orphan*/  mod_hdr; struct mlx5e_mod_hdr_entry* mh; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_4__ {int num_actions; void* actions; } ;
struct mlx5e_mod_hdr_entry {int compl_result; int /*<<< orphan*/  res_ready; int /*<<< orphan*/  modify_hdr; int /*<<< orphan*/  flows_lock; int /*<<< orphan*/  flows; TYPE_1__ key; int /*<<< orphan*/  mod_hdr_hlist; int /*<<< orphan*/  refcnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  modify_hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  modify_hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX5_MH_ACT_SZ ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int get_flow_name_space (struct mlx5e_tc_flow*) ; 
 struct mod_hdr_tbl* get_mod_hdr_table (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_mod_hdr_info (struct mod_hdr_key*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mlx5e_mod_hdr_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_modify_header_alloc (int /*<<< orphan*/ ,int,int,void*) ; 
 scalar_t__ mlx5e_is_eswitch_flow (struct mlx5e_tc_flow*) ; 
 struct mlx5e_mod_hdr_entry* mlx5e_mod_hdr_get (struct mod_hdr_tbl*,struct mod_hdr_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_mod_hdr_put (struct mlx5e_priv*,struct mlx5e_mod_hdr_entry*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_attach_mod_hdr(struct mlx5e_priv *priv,
				struct mlx5e_tc_flow *flow,
				struct mlx5e_tc_flow_parse_attr *parse_attr)
{
	int num_actions, actions_size, namespace, err;
	struct mlx5e_mod_hdr_entry *mh;
	struct mod_hdr_tbl *tbl;
	struct mod_hdr_key key;
	u32 hash_key;

	num_actions  = parse_attr->num_mod_hdr_actions;
	actions_size = MLX5_MH_ACT_SZ * num_actions;

	key.actions = parse_attr->mod_hdr_actions;
	key.num_actions = num_actions;

	hash_key = hash_mod_hdr_info(&key);

	namespace = get_flow_name_space(flow);
	tbl = get_mod_hdr_table(priv, namespace);

	mutex_lock(&tbl->lock);
	mh = mlx5e_mod_hdr_get(tbl, &key, hash_key);
	if (mh) {
		mutex_unlock(&tbl->lock);
		wait_for_completion(&mh->res_ready);

		if (mh->compl_result < 0) {
			err = -EREMOTEIO;
			goto attach_header_err;
		}
		goto attach_flow;
	}

	mh = kzalloc(sizeof(*mh) + actions_size, GFP_KERNEL);
	if (!mh) {
		mutex_unlock(&tbl->lock);
		return -ENOMEM;
	}

	mh->key.actions = (void *)mh + sizeof(*mh);
	memcpy(mh->key.actions, key.actions, actions_size);
	mh->key.num_actions = num_actions;
	spin_lock_init(&mh->flows_lock);
	INIT_LIST_HEAD(&mh->flows);
	refcount_set(&mh->refcnt, 1);
	init_completion(&mh->res_ready);

	hash_add(tbl->hlist, &mh->mod_hdr_hlist, hash_key);
	mutex_unlock(&tbl->lock);

	mh->modify_hdr = mlx5_modify_header_alloc(priv->mdev, namespace,
						  mh->key.num_actions,
						  mh->key.actions);
	if (IS_ERR(mh->modify_hdr)) {
		err = PTR_ERR(mh->modify_hdr);
		mh->compl_result = err;
		goto alloc_header_err;
	}
	mh->compl_result = 1;
	complete_all(&mh->res_ready);

attach_flow:
	flow->mh = mh;
	spin_lock(&mh->flows_lock);
	list_add(&flow->mod_hdr, &mh->flows);
	spin_unlock(&mh->flows_lock);
	if (mlx5e_is_eswitch_flow(flow))
		flow->esw_attr->modify_hdr = mh->modify_hdr;
	else
		flow->nic_attr->modify_hdr = mh->modify_hdr;

	return 0;

alloc_header_err:
	complete_all(&mh->res_ready);
attach_header_err:
	mlx5e_mod_hdr_put(priv, mh, namespace);
	return err;
}