#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* di_map; TYPE_1__* serio_map; } ;
typedef  TYPE_2__ hil_mlc ;
struct TYPE_4__ {int di_revmap; } ;

/* Variables and functions */
 int HIL_MLC_DEVMEM ; 

__attribute__((used)) static inline void hil_mlc_clean_serio_map(hil_mlc *mlc)
{
	int idx;

	for (idx = 0; idx < HIL_MLC_DEVMEM; idx++) {
		int j, found = 0;

		for (j = 0; j < 7 ; j++)
			if (mlc->di_map[j] == idx)
				found++;

		if (!found)
			mlc->serio_map[idx].di_revmap = -1;
	}
}