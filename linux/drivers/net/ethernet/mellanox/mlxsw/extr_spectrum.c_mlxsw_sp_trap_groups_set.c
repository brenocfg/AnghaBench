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
typedef  int u8 ;
typedef  int u16 ;
struct mlxsw_core {int dummy; } ;
typedef  enum mlxsw_reg_htgt_trap_group { ____Placeholder_mlxsw_reg_htgt_trap_group } mlxsw_reg_htgt_trap_group ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAX_CPU_POLICERS ; 
 int /*<<< orphan*/  MAX_TRAP_GROUPS ; 
 int MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_HTGT_DEFAULT_PRIORITY ; 
 int MLXSW_REG_HTGT_DEFAULT_TC ; 
 int MLXSW_REG_HTGT_INVALID_POLICER ; 
 int MLXSW_REG_HTGT_LEN ; 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_ARP 148 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_BGP 147 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_DHCP 146 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_EVENT 145 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_HOST_MISS 144 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_IGMP 143 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_IP2ME 142 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_MLD 141 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_ND 140 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_LACP 139 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_LBERROR 138 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_LLDP 137 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST 136 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_OSPF 135 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_PIM 134 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP0 133 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP1 132 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_REMOTE_ROUTE 131 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP 130 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_RPF 129 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_STP 128 
 int /*<<< orphan*/  htgt ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_pack (char*,int,int,int,int) ; 
 int mlxsw_reg_write (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp_trap_groups_set(struct mlxsw_core *mlxsw_core)
{
	char htgt_pl[MLXSW_REG_HTGT_LEN];
	enum mlxsw_reg_htgt_trap_group i;
	int max_cpu_policers;
	int max_trap_groups;
	u8 priority, tc;
	u16 policer_id;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_TRAP_GROUPS))
		return -EIO;

	max_trap_groups = MLXSW_CORE_RES_GET(mlxsw_core, MAX_TRAP_GROUPS);
	max_cpu_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_CPU_POLICERS);

	for (i = 0; i < max_trap_groups; i++) {
		policer_id = i;
		switch (i) {
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_STP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LACP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LLDP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_OSPF:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PIM:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP0:
			priority = 5;
			tc = 5;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_BGP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_DHCP:
			priority = 4;
			tc = 4;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IGMP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IP2ME:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_MLD:
			priority = 3;
			tc = 3;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_ARP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_ND:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_RPF:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP1:
			priority = 2;
			tc = 2;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_HOST_MISS:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_REMOTE_ROUTE:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LBERROR:
			priority = 1;
			tc = 1;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_EVENT:
			priority = MLXSW_REG_HTGT_DEFAULT_PRIORITY;
			tc = MLXSW_REG_HTGT_DEFAULT_TC;
			policer_id = MLXSW_REG_HTGT_INVALID_POLICER;
			break;
		default:
			continue;
		}

		if (max_cpu_policers <= policer_id &&
		    policer_id != MLXSW_REG_HTGT_INVALID_POLICER)
			return -EIO;

		mlxsw_reg_htgt_pack(htgt_pl, i, policer_id, priority, tc);
		err = mlxsw_reg_write(mlxsw_core, MLXSW_REG(htgt), htgt_pl);
		if (err)
			return err;
	}

	return 0;
}