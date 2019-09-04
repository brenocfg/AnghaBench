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
 int /*<<< orphan*/  WARN_ON_FPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_kernel_fpu ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kernel_fpu_disable(void)
{
	WARN_ON_FPU(this_cpu_read(in_kernel_fpu));
	this_cpu_write(in_kernel_fpu, true);
}