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
struct TYPE_3__ {int* di_map; int /*<<< orphan*/  di_scratch; scalar_t__ di; } ;
typedef  TYPE_1__ hil_mlc ;

/* Variables and functions */
 int HIL_MLC_DEVMEM ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hil_mlc_match_di_scratch(hil_mlc *mlc)
{
	int idx;

	for (idx = 0; idx < HIL_MLC_DEVMEM; idx++) {
		int j, found = 0;

		/* In-use slots are not eligible. */
		for (j = 0; j < 7 ; j++)
			if (mlc->di_map[j] == idx)
				found++;

		if (found)
			continue;

		if (!memcmp(mlc->di + idx, &mlc->di_scratch,
				sizeof(mlc->di_scratch)))
			break;
	}
	return idx >= HIL_MLC_DEVMEM ? -1 : idx;
}