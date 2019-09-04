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
 int /*<<< orphan*/  create_branch (unsigned int*,unsigned long,int) ; 
 int patch_instruction (unsigned int*,int /*<<< orphan*/ ) ; 

int patch_branch(unsigned int *addr, unsigned long target, int flags)
{
	return patch_instruction(addr, create_branch(addr, target, flags));
}