#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* di_map; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int HIL_MLC_DEVMEM ; 

__attribute__((used)) static int hil_mlc_find_free_di(hil_mlc *mlc)
{
	int idx;

	/* TODO: Pick all-zero slots first, failing that,
	 * randomize the slot picked among those eligible.
	 */
	for (idx = 0; idx < HIL_MLC_DEVMEM; idx++) {
		int j, found = 0;

		for (j = 0; j < 7 ; j++)
			if (mlc->di_map[j] == idx)
				found++;

		if (!found)
			break;
	}

	return idx; /* Note: It is guaranteed at least one above will match */
}