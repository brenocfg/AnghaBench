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
 int /*<<< orphan*/  DF ; 
 int /*<<< orphan*/  DF_CS_AON0_CoherentSlaveModeCtrlA0 ; 
 int /*<<< orphan*/  ForceParWrRMW ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void df_v1_7_enable_ecc_force_par_wr_rmw(struct amdgpu_device *adev,
						bool enable)
{
	WREG32_FIELD15(DF, 0, DF_CS_AON0_CoherentSlaveModeCtrlA0,
		       ForceParWrRMW, enable);
}