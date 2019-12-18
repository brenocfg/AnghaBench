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
struct mlxsw_sp_upper {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  lags; int /*<<< orphan*/  core; int /*<<< orphan*/  base_mac; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_LAG ; 
 int /*<<< orphan*/  MAX_LAG_MEMBERS ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SLCR_LAG_HASH_DIP ; 
 int MLXSW_REG_SLCR_LAG_HASH_DMAC ; 
 int MLXSW_REG_SLCR_LAG_HASH_DPORT ; 
 int MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE ; 
 int MLXSW_REG_SLCR_LAG_HASH_IPPROTO ; 
 int MLXSW_REG_SLCR_LAG_HASH_SIP ; 
 int MLXSW_REG_SLCR_LAG_HASH_SMAC ; 
 int MLXSW_REG_SLCR_LAG_HASH_SPORT ; 
 int MLXSW_REG_SLCR_LAG_HASH_VLANID ; 
 int MLXSW_REG_SLCR_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_LAG_SEED_INIT ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_slcr_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  slcr ; 

__attribute__((used)) static int mlxsw_sp_lag_init(struct mlxsw_sp *mlxsw_sp)
{
	char slcr_pl[MLXSW_REG_SLCR_LEN];
	u32 seed;
	int err;

	seed = jhash(mlxsw_sp->base_mac, sizeof(mlxsw_sp->base_mac),
		     MLXSW_SP_LAG_SEED_INIT);
	mlxsw_reg_slcr_pack(slcr_pl, MLXSW_REG_SLCR_LAG_HASH_SMAC |
				     MLXSW_REG_SLCR_LAG_HASH_DMAC |
				     MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE |
				     MLXSW_REG_SLCR_LAG_HASH_VLANID |
				     MLXSW_REG_SLCR_LAG_HASH_SIP |
				     MLXSW_REG_SLCR_LAG_HASH_DIP |
				     MLXSW_REG_SLCR_LAG_HASH_SPORT |
				     MLXSW_REG_SLCR_LAG_HASH_DPORT |
				     MLXSW_REG_SLCR_LAG_HASH_IPPROTO, seed);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(slcr), slcr_pl);
	if (err)
		return err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_LAG) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_LAG_MEMBERS))
		return -EIO;

	mlxsw_sp->lags = kcalloc(MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_LAG),
				 sizeof(struct mlxsw_sp_upper),
				 GFP_KERNEL);
	if (!mlxsw_sp->lags)
		return -ENOMEM;

	return 0;
}