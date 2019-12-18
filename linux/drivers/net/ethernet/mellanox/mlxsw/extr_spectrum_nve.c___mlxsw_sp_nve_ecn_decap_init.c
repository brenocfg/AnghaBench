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
 int /*<<< orphan*/  INET_ECN_CE ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TNDEM_LEN ; 
 int /*<<< orphan*/  MLXSW_TRAP_ID_DECAP_ECN0 ; 
 int /*<<< orphan*/  __INET_ECN_decapsulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlxsw_reg_tndem_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tndem ; 

__attribute__((used)) static int __mlxsw_sp_nve_ecn_decap_init(struct mlxsw_sp *mlxsw_sp,
					 u8 inner_ecn, u8 outer_ecn)
{
	char tndem_pl[MLXSW_REG_TNDEM_LEN];
	bool trap_en, set_ce = false;
	u8 new_inner_ecn;

	trap_en = !!__INET_ECN_decapsulate(outer_ecn, inner_ecn, &set_ce);
	new_inner_ecn = set_ce ? INET_ECN_CE : inner_ecn;

	mlxsw_reg_tndem_pack(tndem_pl, outer_ecn, inner_ecn, new_inner_ecn,
			     trap_en, trap_en ? MLXSW_TRAP_ID_DECAP_ECN0 : 0);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tndem), tndem_pl);
}