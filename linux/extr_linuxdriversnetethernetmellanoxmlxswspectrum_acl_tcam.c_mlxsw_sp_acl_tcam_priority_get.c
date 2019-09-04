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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct mlxsw_sp_acl_rule_info {scalar_t__ priority; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KVD_SIZE ; 
 scalar_t__ MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_sp_acl_tcam_priority_get(struct mlxsw_sp *mlxsw_sp,
				   struct mlxsw_sp_acl_rule_info *rulei,
				   u32 *priority, bool fillup_priority)
{
	u64 max_priority;

	if (!fillup_priority) {
		*priority = 0;
		return 0;
	}

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, KVD_SIZE))
		return -EIO;

	/* Priority range is 1..cap_kvd_size-1. */
	max_priority = MLXSW_CORE_RES_GET(mlxsw_sp->core, KVD_SIZE) - 1;
	if (rulei->priority >= max_priority)
		return -EINVAL;

	/* Unlike in TC, in HW, higher number means higher priority. */
	*priority = max_priority - rulei->priority;
	return 0;
}