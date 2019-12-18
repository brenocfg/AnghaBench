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
 int SDW_FRAME_ROWS ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* sdw_rows ; 

int sdw_find_row_index(int row)
{
	int i;

	for (i = 0; i < SDW_FRAME_ROWS; i++) {
		if (sdw_rows[i] == row)
			return i;
	}

	pr_warn("Requested row not found, selecting lowest row no: 48\n");
	return 0;
}