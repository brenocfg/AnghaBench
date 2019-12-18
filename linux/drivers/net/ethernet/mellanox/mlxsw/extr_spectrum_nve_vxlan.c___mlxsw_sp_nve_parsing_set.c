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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MPRS_LEN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mprs_pack (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mprs ; 

__attribute__((used)) static int __mlxsw_sp_nve_parsing_set(struct mlxsw_sp *mlxsw_sp,
				      unsigned int parsing_depth,
				      __be16 udp_dport)
{
	char mprs_pl[MLXSW_REG_MPRS_LEN];

	mlxsw_reg_mprs_pack(mprs_pl, parsing_depth, be16_to_cpu(udp_dport));
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mprs), mprs_pl);
}