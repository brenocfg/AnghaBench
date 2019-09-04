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
struct mlxsw_sp1_kvdl_part_info {int end_index; int start_index; int alloc_size; } ;
struct mlxsw_sp1_kvdl_part {int /*<<< orphan*/  usage; struct mlxsw_sp1_kvdl_part_info info; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_sp1_kvdl_to_kvdl_index (struct mlxsw_sp1_kvdl_part_info const*,unsigned int) ; 

__attribute__((used)) static int mlxsw_sp1_kvdl_part_alloc(struct mlxsw_sp1_kvdl_part *part,
				     u32 *p_kvdl_index)
{
	const struct mlxsw_sp1_kvdl_part_info *info = &part->info;
	unsigned int entry_index, nr_entries;

	nr_entries = (info->end_index - info->start_index + 1) /
		     info->alloc_size;
	entry_index = find_first_zero_bit(part->usage, nr_entries);
	if (entry_index == nr_entries)
		return -ENOBUFS;
	__set_bit(entry_index, part->usage);

	*p_kvdl_index = mlxsw_sp1_kvdl_to_kvdl_index(info, entry_index);

	return 0;
}