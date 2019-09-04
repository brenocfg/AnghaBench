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
typedef  int phandle ;

/* Variables and functions */
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 

inline phandle prom_inst2pkg(int inst)
{
	unsigned long args[5];
	phandle node;
	
	args[0] = (unsigned long) "instance-to-package";
	args[1] = 1;
	args[2] = 1;
	args[3] = (unsigned int) inst;
	args[4] = (unsigned long) -1;

	p1275_cmd_direct(args);

	node = (int) args[4];
	if ((s32)node == -1)
		return 0;
	return node;
}