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
 int GET_SPEEDSTEP_OWNER ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int smi_cmd ; 
 int /*<<< orphan*/  smi_port ; 
 int smi_sig ; 
 int virt_to_phys (unsigned char*) ; 

__attribute__((used)) static int speedstep_smi_ownership(void)
{
	u32 command, result, magic, dummy;
	u32 function = GET_SPEEDSTEP_OWNER;
	unsigned char magic_data[] = "Copyright (c) 1999 Intel Corporation";

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);
	magic = virt_to_phys(magic_data);

	pr_debug("trying to obtain ownership with command %x at port %x\n",
			command, smi_port);

	__asm__ __volatile__(
		"push %%ebp\n"
		"out %%al, (%%dx)\n"
		"pop %%ebp\n"
		: "=D" (result),
		  "=a" (dummy), "=b" (dummy), "=c" (dummy), "=d" (dummy),
		  "=S" (dummy)
		: "a" (command), "b" (function), "c" (0), "d" (smi_port),
		  "D" (0), "S" (magic)
		: "memory"
	);

	pr_debug("result is %x\n", result);

	return result;
}