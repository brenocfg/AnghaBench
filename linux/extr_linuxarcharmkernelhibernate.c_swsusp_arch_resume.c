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
 scalar_t__ ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  arch_restore_image ; 
 int /*<<< orphan*/  call_with_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ resume_stack ; 

int swsusp_arch_resume(void)
{
	call_with_stack(arch_restore_image, 0,
		resume_stack + ARRAY_SIZE(resume_stack));
	return 0;
}