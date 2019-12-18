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
 int MLX4_MAX_MGM_LOG_ENTRY_SIZE ; 
 int MLX4_MIN_MGM_LOG_ENTRY_SIZE ; 

__attribute__((used)) static int choose_log_fs_mgm_entry_size(int qp_per_entry)
{
	int i = MLX4_MIN_MGM_LOG_ENTRY_SIZE;

	for (i = MLX4_MIN_MGM_LOG_ENTRY_SIZE; i <= MLX4_MAX_MGM_LOG_ENTRY_SIZE;
	      i++) {
		if (qp_per_entry <= 4 * ((1 << i) / 16 - 2))
			break;
	}

	return (i <= MLX4_MAX_MGM_LOG_ENTRY_SIZE) ? i : -1;
}