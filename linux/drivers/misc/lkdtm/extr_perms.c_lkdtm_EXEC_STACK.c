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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_WRITE ; 
 int EXEC_SIZE ; 
 int /*<<< orphan*/  execute_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lkdtm_EXEC_STACK(void)
{
	u8 stack_area[EXEC_SIZE];
	execute_location(stack_area, CODE_WRITE);
}