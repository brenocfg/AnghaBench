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
struct mlxsw_sp_sb_pm {int /*<<< orphan*/  max_buff; int /*<<< orphan*/  min_buff; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int mlxsw_sp_sb_pm_write (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mlxsw_sp_port_sb_pms_init(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				       enum mlxsw_reg_sbxx_dir dir,
				       const struct mlxsw_sp_sb_pm *pms,
				       size_t pms_len)
{
	int i;
	int err;

	for (i = 0; i < pms_len; i++) {
		const struct mlxsw_sp_sb_pm *pm;

		pm = &pms[i];
		err = mlxsw_sp_sb_pm_write(mlxsw_sp, local_port, i, dir,
					   pm->min_buff, pm->max_buff);
		if (err)
			return err;
	}
	return 0;
}