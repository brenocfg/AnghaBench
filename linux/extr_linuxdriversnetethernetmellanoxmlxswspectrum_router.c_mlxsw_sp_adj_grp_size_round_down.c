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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void mlxsw_sp_adj_grp_size_round_down(u16 *p_adj_grp_size,
					     unsigned int alloc_size)
{
	if (alloc_size >= 4096)
		*p_adj_grp_size = 4096;
	else if (alloc_size >= 2048)
		*p_adj_grp_size = 2048;
	else if (alloc_size >= 1024)
		*p_adj_grp_size = 1024;
	else if (alloc_size >= 512)
		*p_adj_grp_size = 512;
}