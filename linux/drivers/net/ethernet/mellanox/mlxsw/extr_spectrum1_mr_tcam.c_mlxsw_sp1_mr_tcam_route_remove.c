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
struct parman_item {int /*<<< orphan*/  index; } ;
struct mlxsw_sp_mr_route_key {int proto; int /*<<< orphan*/  vrid; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct in6_addr IN6ADDR_ANY_INIT ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RMFT2_LEN ; 
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  mlxsw_reg_rmft2_ipv4_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_reg_rmft2_ipv6_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_addr,struct in6_addr,struct in6_addr,struct in6_addr,int /*<<< orphan*/ *) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rmft2 ; 

__attribute__((used)) static int mlxsw_sp1_mr_tcam_route_remove(struct mlxsw_sp *mlxsw_sp,
					  struct parman_item *parman_item,
					  struct mlxsw_sp_mr_route_key *key)
{
	struct in6_addr zero_addr = IN6ADDR_ANY_INIT;
	char rmft2_pl[MLXSW_REG_RMFT2_LEN];

	switch (key->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_reg_rmft2_ipv4_pack(rmft2_pl, false, parman_item->index,
					  key->vrid, 0, 0, 0, 0, 0, 0, NULL);
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_rmft2_ipv6_pack(rmft2_pl, false, parman_item->index,
					  key->vrid, 0, 0, zero_addr, zero_addr,
					  zero_addr, zero_addr, NULL);
		break;
	}

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rmft2), rmft2_pl);
}