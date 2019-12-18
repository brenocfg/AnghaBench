#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct mlxsw_sp2_kvdl_part {unsigned int indexes_per_usage_bit; int /*<<< orphan*/  usage; TYPE_1__* info; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  res_type; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp2_kvdl_rec_del (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void mlxsw_sp2_kvdl_part_free(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp2_kvdl_part *part,
				     unsigned int size, u32 kvdl_index)
{
	unsigned int bit_count;
	unsigned int bit;
	unsigned int i;
	int err;

	/* We need to ask FW to delete previously used KVD linear index */
	err = mlxsw_sp2_kvdl_rec_del(mlxsw_sp, part->info->res_type,
				     size, kvdl_index);
	if (err)
		return;

	bit_count = DIV_ROUND_UP(size, part->indexes_per_usage_bit);
	bit = kvdl_index / part->indexes_per_usage_bit;
	for (i = 0; i < bit_count; i++)
		__clear_bit(bit + i, part->usage);
}