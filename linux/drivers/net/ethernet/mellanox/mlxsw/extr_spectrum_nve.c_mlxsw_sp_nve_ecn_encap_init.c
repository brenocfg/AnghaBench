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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int INET_ECN_CE ; 
 int INET_ECN_NOT_ECT ; 
 int /*<<< orphan*/  INET_ECN_encapsulate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TNEEM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_tneem_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tneem ; 

__attribute__((used)) static int mlxsw_sp_nve_ecn_encap_init(struct mlxsw_sp *mlxsw_sp)
{
	int i;

	/* Iterate over inner ECN values */
	for (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) {
		u8 outer_ecn = INET_ECN_encapsulate(0, i);
		char tneem_pl[MLXSW_REG_TNEEM_LEN];
		int err;

		mlxsw_reg_tneem_pack(tneem_pl, i, outer_ecn);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tneem),
				      tneem_pl);
		if (err)
			return err;
	}

	return 0;
}