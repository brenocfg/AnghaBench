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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_program_display_gap (struct amdgpu_device*) ; 

__attribute__((used)) static void si_dpm_display_configuration_changed(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	si_program_display_gap(adev);
}