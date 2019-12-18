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
struct smu_context {TYPE_1__* adev; } ;
struct TYPE_2__ {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  SMU_MSG_SetGfxCGPG ; 
 int smu_v12_0_send_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v12_0_set_gfx_cgpg(struct smu_context *smu, bool enable)
{
	if (!(smu->adev->pg_flags & AMD_PG_SUPPORT_GFX_PG))
		return 0;

	return smu_v12_0_send_msg_with_param(smu,
		SMU_MSG_SetGfxCGPG, enable ? 1 : 0);
}