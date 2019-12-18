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
typedef  scalar_t__ u32 ;
struct mlxsw_sp1_kvdl_part_info {unsigned int alloc_size; scalar_t__ start_index; } ;

/* Variables and functions */

__attribute__((used)) static u32
mlxsw_sp1_kvdl_to_kvdl_index(const struct mlxsw_sp1_kvdl_part_info *info,
			     unsigned int entry_index)
{
	return info->start_index + entry_index * info->alloc_size;
}