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
union mlxsw_sp_l3addr {int /*<<< orphan*/  addr4; } ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 int EINVAL ; 
#define  MLXSW_SP_L3_PROTO_IPV4 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

int mlxsw_sp_nve_learned_ip_resolve(struct mlxsw_sp *mlxsw_sp, u32 uip,
				    enum mlxsw_sp_l3proto proto,
				    union mlxsw_sp_l3addr *addr)
{
	switch (proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		addr->addr4 = cpu_to_be32(uip);
		return 0;
	default:
		WARN_ON(1);
		return -EINVAL;
	}
}