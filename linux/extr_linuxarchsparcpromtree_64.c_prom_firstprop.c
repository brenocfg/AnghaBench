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
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 
 scalar_t__ prom_nextprop_name ; 

char *prom_firstprop(phandle node, char *buffer)
{
	unsigned long args[7];

	*buffer = 0;
	if ((s32)node == -1)
		return buffer;

	args[0] = (unsigned long) prom_nextprop_name;
	args[1] = 3;
	args[2] = 1;
	args[3] = (unsigned int) node;
	args[4] = 0;
	args[5] = (unsigned long) buffer;
	args[6] = (unsigned long) -1;

	p1275_cmd_direct(args);

	return buffer;
}