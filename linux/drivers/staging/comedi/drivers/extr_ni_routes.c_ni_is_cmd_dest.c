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
 int ARRAY_SIZE (int*) ; 
 int* NI_CMD_DESTS ; 

bool ni_is_cmd_dest(int dest)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(NI_CMD_DESTS); ++i)
		if (NI_CMD_DESTS[i] == dest)
			return true;
	return false;
}