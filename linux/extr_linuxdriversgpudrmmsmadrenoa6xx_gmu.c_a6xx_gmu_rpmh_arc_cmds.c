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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cmd_db_read_aux_data (char const*,void*,int) ; 
 int cmd_db_read_aux_data_len (char const*) ; 

__attribute__((used)) static int a6xx_gmu_rpmh_arc_cmds(const char *id, void *vals, int size)
{
	u32 len = cmd_db_read_aux_data_len(id);

	if (!len)
		return 0;

	if (WARN_ON(len > size))
		return -EINVAL;

	cmd_db_read_aux_data(id, vals, len);

	/*
	 * The data comes back as an array of unsigned shorts so adjust the
	 * count accordingly
	 */
	return len >> 1;
}