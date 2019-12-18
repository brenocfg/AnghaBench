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
struct ras_cure_if {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

int amdgpu_ras_error_cure(struct amdgpu_device *adev,
		struct ras_cure_if *info)
{
	/* psp fw has no cure interface for now. */
	return 0;
}