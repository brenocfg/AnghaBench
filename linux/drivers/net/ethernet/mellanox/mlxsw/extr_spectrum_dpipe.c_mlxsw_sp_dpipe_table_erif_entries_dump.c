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
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink_dpipe_value {int dummy; } ;
struct devlink_dpipe_match {int /*<<< orphan*/  member_0; } ;
struct devlink_dpipe_entry {int /*<<< orphan*/  member_0; } ;
struct devlink_dpipe_dump_ctx {int dummy; } ;
struct devlink_dpipe_action {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  match_value ;
typedef  int /*<<< orphan*/  action_value ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  MAX_RIFS ; 
 unsigned int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_dpipe_entry_clear (struct devlink_dpipe_entry*) ; 
 int devlink_dpipe_entry_ctx_append (struct devlink_dpipe_dump_ctx*,struct devlink_dpipe_entry*) ; 
 int /*<<< orphan*/  devlink_dpipe_entry_ctx_close (struct devlink_dpipe_dump_ctx*) ; 
 int devlink_dpipe_entry_ctx_prepare (struct devlink_dpipe_dump_ctx*) ; 
 int /*<<< orphan*/  memset (struct devlink_dpipe_value*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_erif_entry_get (struct mlxsw_sp*,struct devlink_dpipe_entry*,struct mlxsw_sp_rif*,int) ; 
 int mlxsw_sp_erif_entry_prepare (struct devlink_dpipe_entry*,struct devlink_dpipe_value*,struct devlink_dpipe_match*,struct devlink_dpipe_value*,struct devlink_dpipe_action*) ; 
 int /*<<< orphan*/  mlxsw_sp_erif_match_action_prepare (struct devlink_dpipe_match*,struct devlink_dpipe_action*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_by_index (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_dev (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int
mlxsw_sp_dpipe_table_erif_entries_dump(void *priv, bool counters_enabled,
				       struct devlink_dpipe_dump_ctx *dump_ctx)
{
	struct devlink_dpipe_value match_value, action_value;
	struct devlink_dpipe_action action = {0};
	struct devlink_dpipe_match match = {0};
	struct devlink_dpipe_entry entry = {0};
	struct mlxsw_sp *mlxsw_sp = priv;
	unsigned int rif_count;
	int i, j;
	int err;

	memset(&match_value, 0, sizeof(match_value));
	memset(&action_value, 0, sizeof(action_value));

	mlxsw_sp_erif_match_action_prepare(&match, &action);
	err = mlxsw_sp_erif_entry_prepare(&entry, &match_value, &match,
					  &action_value, &action);
	if (err)
		return err;

	rif_count = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);
	rtnl_lock();
	i = 0;
start_again:
	err = devlink_dpipe_entry_ctx_prepare(dump_ctx);
	if (err)
		return err;
	j = 0;
	for (; i < rif_count; i++) {
		struct mlxsw_sp_rif *rif = mlxsw_sp_rif_by_index(mlxsw_sp, i);

		if (!rif || !mlxsw_sp_rif_dev(rif))
			continue;
		err = mlxsw_sp_erif_entry_get(mlxsw_sp, &entry, rif,
					      counters_enabled);
		if (err)
			goto err_entry_get;
		err = devlink_dpipe_entry_ctx_append(dump_ctx, &entry);
		if (err) {
			if (err == -EMSGSIZE) {
				if (!j)
					goto err_entry_append;
				break;
			}
			goto err_entry_append;
		}
		j++;
	}

	devlink_dpipe_entry_ctx_close(dump_ctx);
	if (i != rif_count)
		goto start_again;
	rtnl_unlock();

	devlink_dpipe_entry_clear(&entry);
	return 0;
err_entry_append:
err_entry_get:
	rtnl_unlock();
	devlink_dpipe_entry_clear(&entry);
	return err;
}