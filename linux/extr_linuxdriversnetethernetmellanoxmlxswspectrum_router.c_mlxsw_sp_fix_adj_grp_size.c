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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int /*<<< orphan*/  mlxsw_sp_adj_grp_size_round_down (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_sp_adj_grp_size_round_up (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_kvdl_alloc_count_query (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlxsw_sp_fix_adj_grp_size(struct mlxsw_sp *mlxsw_sp,
				     u16 *p_adj_grp_size)
{
	unsigned int alloc_size;
	int err;

	/* Round up the requested group size to the next size supported
	 * by the device and make sure the request can be satisfied.
	 */
	mlxsw_sp_adj_grp_size_round_up(p_adj_grp_size);
	err = mlxsw_sp_kvdl_alloc_count_query(mlxsw_sp,
					      MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
					      *p_adj_grp_size, &alloc_size);
	if (err)
		return err;
	/* It is possible the allocation results in more allocated
	 * entries than requested. Try to use as much of them as
	 * possible.
	 */
	mlxsw_sp_adj_grp_size_round_down(p_adj_grp_size, alloc_size);

	return 0;
}