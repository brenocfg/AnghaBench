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
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2_PWROFF_LO ; 
 int /*<<< orphan*/  SHADER_PWROFF_LO ; 
 int /*<<< orphan*/  STACK_PWROFF_LO ; 
 int /*<<< orphan*/  TILER_PWROFF_LO ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void panfrost_gpu_power_off(struct panfrost_device *pfdev)
{
	gpu_write(pfdev, TILER_PWROFF_LO, 0);
	gpu_write(pfdev, SHADER_PWROFF_LO, 0);
	gpu_write(pfdev, STACK_PWROFF_LO, 0);
	gpu_write(pfdev, L2_PWROFF_LO, 0);
}