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

/* Variables and functions */
 int /*<<< orphan*/  VXGE_DRIVER_NAME ; 
 int /*<<< orphan*/  VXGE_ERR ; 
 int VXGE_HW_MAX_VIRTUAL_PATHS ; 
 int VXGE_HW_VPATH_BANDWIDTH_MAX ; 
 int* bw_percentage ; 
 int /*<<< orphan*/  vxge_debug_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify_bandwidth(void)
{
	int i, band_width, total = 0, equal_priority = 0;

	/* 1. If user enters 0 for some fifo, give equal priority to all */
	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {
		if (bw_percentage[i] == 0) {
			equal_priority = 1;
			break;
		}
	}

	if (!equal_priority) {
		/* 2. If sum exceeds 100, give equal priority to all */
		for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {
			if (bw_percentage[i] == 0xFF)
				break;

			total += bw_percentage[i];
			if (total > VXGE_HW_VPATH_BANDWIDTH_MAX) {
				equal_priority = 1;
				break;
			}
		}
	}

	if (!equal_priority) {
		/* Is all the bandwidth consumed? */
		if (total < VXGE_HW_VPATH_BANDWIDTH_MAX) {
			if (i < VXGE_HW_MAX_VIRTUAL_PATHS) {
				/* Split rest of bw equally among next VPs*/
				band_width =
				  (VXGE_HW_VPATH_BANDWIDTH_MAX  - total) /
					(VXGE_HW_MAX_VIRTUAL_PATHS - i);
				if (band_width < 2) /* min of 2% */
					equal_priority = 1;
				else {
					for (; i < VXGE_HW_MAX_VIRTUAL_PATHS;
						i++)
						bw_percentage[i] =
							band_width;
				}
			}
		} else if (i < VXGE_HW_MAX_VIRTUAL_PATHS)
			equal_priority = 1;
	}

	if (equal_priority) {
		vxge_debug_init(VXGE_ERR,
			"%s: Assigning equal bandwidth to all the vpaths",
			VXGE_DRIVER_NAME);
		bw_percentage[0] = VXGE_HW_VPATH_BANDWIDTH_MAX /
					VXGE_HW_MAX_VIRTUAL_PATHS;
		for (i = 1; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++)
			bw_percentage[i] = bw_percentage[0];
	}
}