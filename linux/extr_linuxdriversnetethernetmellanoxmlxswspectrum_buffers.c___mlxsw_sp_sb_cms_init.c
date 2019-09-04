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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_sb_cm {int /*<<< orphan*/  pool; int /*<<< orphan*/  max_buff; int /*<<< orphan*/  min_buff; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_cm_write (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mlxsw_sp_sb_cms_init(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				  enum mlxsw_reg_sbxx_dir dir,
				  const struct mlxsw_sp_sb_cm *cms,
				  size_t cms_len)
{
	int i;
	int err;

	for (i = 0; i < cms_len; i++) {
		const struct mlxsw_sp_sb_cm *cm;
		u32 min_buff;

		if (i == 8 && dir == MLXSW_REG_SBXX_DIR_INGRESS)
			continue; /* PG number 8 does not exist, skip it */
		cm = &cms[i];
		/* All pools are initialized using dynamic thresholds,
		 * therefore 'max_buff' isn't specified in cells.
		 */
		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, cm->min_buff);
		err = mlxsw_sp_sb_cm_write(mlxsw_sp, local_port, i, dir,
					   min_buff, cm->max_buff, cm->pool);
		if (err)
			return err;
	}
	return 0;
}