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
 int hvcs_index_count ; 
 int* hvcs_index_list ; 

__attribute__((used)) static void hvcs_return_index(int index)
{
	/* Paranoia check */
	if (!hvcs_index_list)
		return;
	if (index < 0 || index >= hvcs_index_count)
		return;
	if (hvcs_index_list[index] == -1)
		return;
	else
		hvcs_index_list[index] = -1;
}