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
struct amdgpu_iv_entry {int dummy; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

__attribute__((used)) static int gfx_v8_0_cp_ecc_error_irq(struct amdgpu_device *adev,
				     struct amdgpu_irq_src *source,
				     struct amdgpu_iv_entry *entry)
{
	DRM_ERROR("CP EDC/ECC error detected.");
	return 0;
}