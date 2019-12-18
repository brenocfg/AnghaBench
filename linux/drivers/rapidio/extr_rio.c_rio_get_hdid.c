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
 int RIO_MAX_MPORTS ; 
 int* hdid ; 
 int ids_num ; 

__attribute__((used)) static int rio_get_hdid(int index)
{
	if (ids_num == 0 || ids_num <= index || index >= RIO_MAX_MPORTS)
		return -1;

	return hdid[index];
}