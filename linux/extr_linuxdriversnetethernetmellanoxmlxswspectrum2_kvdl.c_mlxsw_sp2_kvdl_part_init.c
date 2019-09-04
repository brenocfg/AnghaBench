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
struct mlxsw_sp2_kvdl_part_info {int /*<<< orphan*/  index_range_res_id; int /*<<< orphan*/  usage_bit_count_res_id; } ;
struct mlxsw_sp2_kvdl_part {unsigned int usage_bit_count; unsigned int indexes_per_usage_bit; unsigned int last_allocated_bit; struct mlxsw_sp2_kvdl_part_info const* info; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int BITS_TO_LONGS (unsigned int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxsw_sp2_kvdl_part* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_sp2_kvdl_part* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int mlxsw_core_res_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_res_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp2_kvdl_part *
mlxsw_sp2_kvdl_part_init(struct mlxsw_sp *mlxsw_sp,
			 const struct mlxsw_sp2_kvdl_part_info *info)
{
	unsigned int indexes_per_usage_bit;
	struct mlxsw_sp2_kvdl_part *part;
	unsigned int index_range;
	unsigned int usage_bit_count;
	size_t usage_size;

	if (!mlxsw_core_res_valid(mlxsw_sp->core,
				  info->usage_bit_count_res_id) ||
	    !mlxsw_core_res_valid(mlxsw_sp->core,
				  info->index_range_res_id))
		return ERR_PTR(-EIO);
	usage_bit_count = mlxsw_core_res_get(mlxsw_sp->core,
					     info->usage_bit_count_res_id);
	index_range = mlxsw_core_res_get(mlxsw_sp->core,
					 info->index_range_res_id);

	/* For some partitions, one usage bit represents a group of indexes.
	 * That's why we compute the number of indexes per usage bit here,
	 * according to queried resources.
	 */
	indexes_per_usage_bit = index_range / usage_bit_count;

	usage_size = BITS_TO_LONGS(usage_bit_count) * sizeof(unsigned long);
	part = kzalloc(sizeof(*part) + usage_size, GFP_KERNEL);
	if (!part)
		return ERR_PTR(-ENOMEM);
	part->info = info;
	part->usage_bit_count = usage_bit_count;
	part->indexes_per_usage_bit = indexes_per_usage_bit;
	part->last_allocated_bit = usage_bit_count - 1;
	return part;
}