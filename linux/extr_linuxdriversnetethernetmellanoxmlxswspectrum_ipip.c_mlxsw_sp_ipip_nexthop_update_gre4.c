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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_ipip_entry {int /*<<< orphan*/  ol_dev; int /*<<< orphan*/  ol_lb; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RATR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY ; 
 int /*<<< orphan*/  MLXSW_REG_RATR_TYPE_IPIP ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_ipip4_entry_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ratr_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_lb_rif_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_netdev_daddr4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ratr ; 

__attribute__((used)) static int
mlxsw_sp_ipip_nexthop_update_gre4(struct mlxsw_sp *mlxsw_sp, u32 adj_index,
				  struct mlxsw_sp_ipip_entry *ipip_entry)
{
	u16 rif_index = mlxsw_sp_ipip_lb_rif_index(ipip_entry->ol_lb);
	__be32 daddr4 = mlxsw_sp_ipip_netdev_daddr4(ipip_entry->ol_dev);
	char ratr_pl[MLXSW_REG_RATR_LEN];

	mlxsw_reg_ratr_pack(ratr_pl, MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY,
			    true, MLXSW_REG_RATR_TYPE_IPIP,
			    adj_index, rif_index);
	mlxsw_reg_ratr_ipip4_entry_pack(ratr_pl, be32_to_cpu(daddr4));

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ratr), ratr_pl);
}