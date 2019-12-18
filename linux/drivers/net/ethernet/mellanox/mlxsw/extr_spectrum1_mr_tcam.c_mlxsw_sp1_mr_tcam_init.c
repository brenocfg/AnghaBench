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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp1_mr_tcam_region {int dummy; } ;
struct mlxsw_sp1_mr_tcam {struct mlxsw_sp1_mr_tcam_region* tcam_regions; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_TCAM_RULES ; 
 int EIO ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_RTAR_KEY_TYPE_IPV4_MULTICAST ; 
 int /*<<< orphan*/  MLXSW_REG_RTAR_KEY_TYPE_IPV6_MULTICAST ; 
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 int /*<<< orphan*/  mlxsw_sp1_mr_tcam_region_fini (struct mlxsw_sp1_mr_tcam_region*) ; 
 int mlxsw_sp1_mr_tcam_region_init (struct mlxsw_sp*,struct mlxsw_sp1_mr_tcam_region*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp1_mr_tcam_init(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	struct mlxsw_sp1_mr_tcam *mr_tcam = priv;
	struct mlxsw_sp1_mr_tcam_region *region = &mr_tcam->tcam_regions[0];
	u32 rtar_key;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_TCAM_RULES))
		return -EIO;

	rtar_key = MLXSW_REG_RTAR_KEY_TYPE_IPV4_MULTICAST;
	err = mlxsw_sp1_mr_tcam_region_init(mlxsw_sp,
					    &region[MLXSW_SP_L3_PROTO_IPV4],
					    rtar_key);
	if (err)
		return err;

	rtar_key = MLXSW_REG_RTAR_KEY_TYPE_IPV6_MULTICAST;
	err = mlxsw_sp1_mr_tcam_region_init(mlxsw_sp,
					    &region[MLXSW_SP_L3_PROTO_IPV6],
					    rtar_key);
	if (err)
		goto err_ipv6_region_init;

	return 0;

err_ipv6_region_init:
	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV4]);
	return err;
}