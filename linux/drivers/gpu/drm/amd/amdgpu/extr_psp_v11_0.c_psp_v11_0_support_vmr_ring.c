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
struct psp_context {int sos_fw_version; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool psp_v11_0_support_vmr_ring(struct psp_context *psp)
{
	if (amdgpu_sriov_vf(psp->adev) && psp->sos_fw_version > 0x80045)
		return true;
	return false;
}