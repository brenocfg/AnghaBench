#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * gmc_funcs; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmc_v8_0_gmc_funcs ; 

__attribute__((used)) static void gmc_v8_0_set_gmc_funcs(struct amdgpu_device *adev)
{
	if (adev->gmc.gmc_funcs == NULL)
		adev->gmc.gmc_funcs = &gmc_v8_0_gmc_funcs;
}