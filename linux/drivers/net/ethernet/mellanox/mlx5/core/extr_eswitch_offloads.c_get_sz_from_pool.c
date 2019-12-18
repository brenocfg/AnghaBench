#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* fdb_left; } ;
struct TYPE_4__ {TYPE_1__ offloads; } ;
struct mlx5_eswitch {TYPE_2__ fdb_table; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* ESW_POOLS ; 

__attribute__((used)) static int
get_sz_from_pool(struct mlx5_eswitch *esw)
{
	int sz = 0, i;

	for (i = 0; i < ARRAY_SIZE(ESW_POOLS); i++) {
		if (esw->fdb_table.offloads.fdb_left[i]) {
			--esw->fdb_table.offloads.fdb_left[i];
			sz = ESW_POOLS[i];
			break;
		}
	}

	return sz;
}