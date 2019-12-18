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
 int SDW_FRAME_COLS ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* sdw_cols ; 

int sdw_find_col_index(int col)
{
	int i;

	for (i = 0; i < SDW_FRAME_COLS; i++) {
		if (sdw_cols[i] == col)
			return i;
	}

	pr_warn("Requested column not found, selecting lowest column no: 2\n");
	return 0;
}