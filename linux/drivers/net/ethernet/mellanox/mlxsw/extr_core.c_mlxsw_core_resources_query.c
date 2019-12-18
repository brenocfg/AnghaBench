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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;
struct mlxsw_res {int dummy; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES ; 
 int MLXSW_CMD_QUERY_RESOURCES_PER_QUERY ; 
 scalar_t__ MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_resource_data_get (char*,int) ; 
 scalar_t__ mlxsw_cmd_mbox_query_resource_id_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_zero (char*) ; 
 int mlxsw_cmd_query_resources (struct mlxsw_core*,char*,int) ; 
 int /*<<< orphan*/  mlxsw_res_parse (struct mlxsw_res*,scalar_t__,int /*<<< orphan*/ ) ; 

int mlxsw_core_resources_query(struct mlxsw_core *mlxsw_core, char *mbox,
			       struct mlxsw_res *res)
{
	int index, i;
	u64 data;
	u16 id;
	int err;

	if (!res)
		return 0;

	mlxsw_cmd_mbox_zero(mbox);

	for (index = 0; index < MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES;
	     index++) {
		err = mlxsw_cmd_query_resources(mlxsw_core, mbox, index);
		if (err)
			return err;

		for (i = 0; i < MLXSW_CMD_QUERY_RESOURCES_PER_QUERY; i++) {
			id = mlxsw_cmd_mbox_query_resource_id_get(mbox, i);
			data = mlxsw_cmd_mbox_query_resource_data_get(mbox, i);

			if (id == MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID)
				return 0;

			mlxsw_res_parse(res, id, data);
		}
	}

	/* If after MLXSW_RESOURCES_QUERY_MAX_QUERIES we still didn't get
	 * MLXSW_RESOURCES_TABLE_END_ID, something went bad in the FW.
	 */
	return -EIO;
}