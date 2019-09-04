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
struct mlxsw_res {int dummy; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; } ;
struct mlxsw_config_profile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVD_DOUBLE_SIZE ; 
 int /*<<< orphan*/  KVD_LINEAR_SIZE ; 
 int /*<<< orphan*/  KVD_SINGLE_SIZE ; 
 int /*<<< orphan*/  MLXSW_RES_SET (struct mlxsw_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_core_kvd_sizes_get (int /*<<< orphan*/ ,struct mlxsw_config_profile const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_pci_profile_get_kvd_sizes(const struct mlxsw_pci *mlxsw_pci,
				const struct mlxsw_config_profile *profile,
				struct mlxsw_res *res)
{
	u64 single_size, double_size, linear_size;
	int err;

	err = mlxsw_core_kvd_sizes_get(mlxsw_pci->core, profile,
				       &single_size, &double_size,
				       &linear_size);
	if (err)
		return err;

	MLXSW_RES_SET(res, KVD_SINGLE_SIZE, single_size);
	MLXSW_RES_SET(res, KVD_DOUBLE_SIZE, double_size);
	MLXSW_RES_SET(res, KVD_LINEAR_SIZE, linear_size);

	return 0;
}