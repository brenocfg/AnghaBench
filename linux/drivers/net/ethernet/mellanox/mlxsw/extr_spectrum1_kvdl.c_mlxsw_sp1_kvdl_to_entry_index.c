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
typedef  unsigned int u32 ;
struct mlxsw_sp1_kvdl_part_info {unsigned int start_index; unsigned int alloc_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
mlxsw_sp1_kvdl_to_entry_index(const struct mlxsw_sp1_kvdl_part_info *info,
			      u32 kvdl_index)
{
	return (kvdl_index - info->start_index) / info->alloc_size;
}