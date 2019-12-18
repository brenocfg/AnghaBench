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
 scalar_t__* bgx_vnic ; 
 int max_bgx_per_node ; 

unsigned bgx_get_map(int node)
{
	int i;
	unsigned map = 0;

	for (i = 0; i < max_bgx_per_node; i++) {
		if (bgx_vnic[(node * max_bgx_per_node) + i])
			map |= (1 << i);
	}

	return map;
}