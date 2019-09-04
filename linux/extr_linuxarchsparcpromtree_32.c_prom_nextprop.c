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
typedef  int s32 ;
typedef  scalar_t__ phandle ;

/* Variables and functions */
 char* __prom_nextprop (scalar_t__,char*) ; 

char *prom_nextprop(phandle node, char *oprop, char *buffer)
{
	if (node == 0 || (s32)node == -1)
		return "";

	return __prom_nextprop(node, oprop);
}