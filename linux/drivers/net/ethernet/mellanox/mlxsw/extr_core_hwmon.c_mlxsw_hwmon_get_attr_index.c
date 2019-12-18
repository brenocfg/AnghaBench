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
 int MLXSW_REG_MTMP_GBOX_INDEX_MIN ; 

__attribute__((used)) static int mlxsw_hwmon_get_attr_index(int index, int count)
{
	if (index >= count)
		return index % count + MLXSW_REG_MTMP_GBOX_INDEX_MIN;

	return index;
}