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
 int /*<<< orphan*/  VCE_CGTT_OVERRIDE ; 
 int /*<<< orphan*/  VCE_RB_ARB_CTRL ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vce_v3_0_override_vce_clock_gating(struct amdgpu_device *adev, bool override)
{
	WREG32_FIELD(VCE_RB_ARB_CTRL, VCE_CGTT_OVERRIDE, override ? 1 : 0);
}