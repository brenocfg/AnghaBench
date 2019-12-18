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
struct TYPE_2__ {unsigned int end_index; unsigned int start_index; } ;
struct mlxsw_sp1_kvdl_part {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static void mlxsw_sp1_kvdl_part_update(struct mlxsw_sp1_kvdl_part *part,
				       struct mlxsw_sp1_kvdl_part *part_prev,
				       unsigned int size)
{
	if (!part_prev) {
		part->info.end_index = size - 1;
	} else {
		part->info.start_index = part_prev->info.end_index + 1;
		part->info.end_index = part->info.start_index + size - 1;
	}
}