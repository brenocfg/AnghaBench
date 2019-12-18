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
typedef  int u64 ;
struct mlxsw_sp_ptp_clock {int /*<<< orphan*/  lock; int /*<<< orphan*/  tc; struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTPPS_LEN ; 
 int MLXSW_REG_MTUTC_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC ; 
 int NSEC_PER_SEC ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtpps_vpin_pack (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtutc_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp1_ptp_ns2cycles (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtpps ; 
 int /*<<< orphan*/  mtutc ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp1_ptp_phc_settime(struct mlxsw_sp_ptp_clock *clock, u64 nsec)
{
	struct mlxsw_core *mlxsw_core = clock->core;
	u64 next_sec, next_sec_in_nsec, cycles;
	char mtutc_pl[MLXSW_REG_MTUTC_LEN];
	char mtpps_pl[MLXSW_REG_MTPPS_LEN];
	int err;

	next_sec = div_u64(nsec, NSEC_PER_SEC) + 1;
	next_sec_in_nsec = next_sec * NSEC_PER_SEC;

	spin_lock_bh(&clock->lock);
	cycles = mlxsw_sp1_ptp_ns2cycles(&clock->tc, next_sec_in_nsec);
	spin_unlock_bh(&clock->lock);

	mlxsw_reg_mtpps_vpin_pack(mtpps_pl, cycles);
	err = mlxsw_reg_write(mlxsw_core, MLXSW_REG(mtpps), mtpps_pl);
	if (err)
		return err;

	mlxsw_reg_mtutc_pack(mtutc_pl,
			     MLXSW_REG_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC,
			     0, next_sec);
	return mlxsw_reg_write(mlxsw_core, MLXSW_REG(mtutc), mtutc_pl);
}