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
struct mlxsw_core {int dummy; } ;
struct mlxsw_config_profile {scalar_t__ kvd_linear_size; scalar_t__ kvd_hash_single_parts; scalar_t__ kvd_hash_double_parts; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KVD_DOUBLE_MIN_SIZE ; 
 int /*<<< orphan*/  KVD_SINGLE_MIN_SIZE ; 
 int /*<<< orphan*/  KVD_SIZE ; 
 scalar_t__ MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_KVD_GRANULARITY ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_HASH_SINGLE ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_LINEAR ; 
 int devlink_resource_size_get (struct devlink*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct devlink* priv_to_devlink (struct mlxsw_core*) ; 
 scalar_t__ rounddown (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_kvd_sizes_get(struct mlxsw_core *mlxsw_core,
				  const struct mlxsw_config_profile *profile,
				  u64 *p_single_size, u64 *p_double_size,
				  u64 *p_linear_size)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_core);
	u32 double_size;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_core, KVD_SINGLE_MIN_SIZE) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_core, KVD_DOUBLE_MIN_SIZE))
		return -EIO;

	/* The hash part is what left of the kvd without the
	 * linear part. It is split to the single size and
	 * double size by the parts ratio from the profile.
	 * Both sizes must be a multiplications of the
	 * granularity from the profile. In case the user
	 * provided the sizes they are obtained via devlink.
	 */
	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					p_linear_size);
	if (err)
		*p_linear_size = profile->kvd_linear_size;

	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE,
					p_double_size);
	if (err) {
		double_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) -
			      *p_linear_size;
		double_size *= profile->kvd_hash_double_parts;
		double_size /= profile->kvd_hash_double_parts +
			       profile->kvd_hash_single_parts;
		*p_double_size = rounddown(double_size,
					   MLXSW_SP_KVD_GRANULARITY);
	}

	err = devlink_resource_size_get(devlink,
					MLXSW_SP_RESOURCE_KVD_HASH_SINGLE,
					p_single_size);
	if (err)
		*p_single_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) -
				 *p_double_size - *p_linear_size;

	/* Check results are legal. */
	if (*p_single_size < MLXSW_CORE_RES_GET(mlxsw_core, KVD_SINGLE_MIN_SIZE) ||
	    *p_double_size < MLXSW_CORE_RES_GET(mlxsw_core, KVD_DOUBLE_MIN_SIZE) ||
	    MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) < *p_linear_size)
		return -EIO;

	return 0;
}