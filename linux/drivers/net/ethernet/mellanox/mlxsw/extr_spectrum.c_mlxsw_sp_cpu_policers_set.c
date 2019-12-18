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
typedef  int u32 ;
struct mlxsw_core {int dummy; } ;
typedef  enum mlxsw_reg_qpcr_ir_units { ____Placeholder_mlxsw_reg_qpcr_ir_units } mlxsw_reg_qpcr_ir_units ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAX_CPU_POLICERS ; 
 int MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_ARP 147 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_BGP 146 
#define  MLXSW_REG_HTGT_TRAP_GROUP_SP_DHCP 145 
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
 int MLXSW_REG_QPCR_IR_UNITS_M ; 
 int MLXSW_REG_QPCR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qpcr_pack (char*,int,int,int,int,int) ; 
 int mlxsw_reg_write (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qpcr ; 

__attribute__((used)) static int mlxsw_sp_cpu_policers_set(struct mlxsw_core *mlxsw_core)
{
	char qpcr_pl[MLXSW_REG_QPCR_LEN];
	enum mlxsw_reg_qpcr_ir_units ir_units;
	int max_cpu_policers;
	bool is_bytes;
	u8 burst_size;
	u32 rate;
	int i, err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_core, MAX_CPU_POLICERS))
		return -EIO;

	max_cpu_policers = MLXSW_CORE_RES_GET(mlxsw_core, MAX_CPU_POLICERS);

	ir_units = MLXSW_REG_QPCR_IR_UNITS_M;
	for (i = 0; i < max_cpu_policers; i++) {
		is_bytes = false;
		switch (i) {
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_STP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LACP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LLDP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_OSPF:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PIM:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_RPF:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_LBERROR:
			rate = 128;
			burst_size = 7;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IGMP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_MLD:
			rate = 16 * 1024;
			burst_size = 10;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_BGP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_ARP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_DHCP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_HOST_MISS:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_REMOTE_ROUTE:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6_ND:
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST:
			rate = 1024;
			burst_size = 7;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_IP2ME:
			rate = 1024;
			burst_size = 7;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP0:
			rate = 24 * 1024;
			burst_size = 12;
			break;
		case MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP1:
			rate = 19 * 1024;
			burst_size = 12;
			break;
		default:
			continue;
		}

		mlxsw_reg_qpcr_pack(qpcr_pl, i, ir_units, is_bytes, rate,
				    burst_size);
		err = mlxsw_reg_write(mlxsw_core, MLXSW_REG(qpcr), qpcr_pl);
		if (err)
			return err;
	}

	return 0;
}