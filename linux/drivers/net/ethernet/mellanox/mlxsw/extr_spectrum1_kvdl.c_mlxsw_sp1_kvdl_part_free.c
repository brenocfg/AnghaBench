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
struct mlxsw_sp1_kvdl_part_info {int dummy; } ;
struct mlxsw_sp1_kvdl_part {int /*<<< orphan*/  usage; struct mlxsw_sp1_kvdl_part_info info; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int mlxsw_sp1_kvdl_to_entry_index (struct mlxsw_sp1_kvdl_part_info const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp1_kvdl_part_free(struct mlxsw_sp1_kvdl_part *part,
				     u32 kvdl_index)
{
	const struct mlxsw_sp1_kvdl_part_info *info = &part->info;
	unsigned int entry_index;

	entry_index = mlxsw_sp1_kvdl_to_entry_index(info, kvdl_index);
	__clear_bit(entry_index, part->usage);
}