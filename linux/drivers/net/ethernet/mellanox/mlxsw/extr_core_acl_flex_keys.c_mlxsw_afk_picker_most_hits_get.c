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
struct mlxsw_afk_picker {TYPE_1__* hits; } ;
struct mlxsw_afk {int blocks_count; } ;
struct TYPE_2__ {int total; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mlxsw_afk_picker_most_hits_get(struct mlxsw_afk *mlxsw_afk,
					  struct mlxsw_afk_picker *picker)
{
	int most_index = -EINVAL; /* Should never happen to return this */
	int most_hits = 0;
	int i;

	for (i = 0; i < mlxsw_afk->blocks_count; i++) {
		if (picker->hits[i].total > most_hits) {
			most_hits = picker->hits[i].total;
			most_index = i;
		}
	}
	return most_index;
}