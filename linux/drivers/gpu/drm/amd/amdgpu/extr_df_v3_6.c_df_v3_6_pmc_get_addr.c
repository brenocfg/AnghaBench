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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int df_v3_6_pmc_config_2_cntr (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smnPerfMonCtlHi0 ; 
 int /*<<< orphan*/  smnPerfMonCtlHi1 ; 
 int /*<<< orphan*/  smnPerfMonCtlHi2 ; 
 int /*<<< orphan*/  smnPerfMonCtlHi3 ; 
 int /*<<< orphan*/  smnPerfMonCtlLo0 ; 
 int /*<<< orphan*/  smnPerfMonCtlLo1 ; 
 int /*<<< orphan*/  smnPerfMonCtlLo2 ; 
 int /*<<< orphan*/  smnPerfMonCtlLo3 ; 
 int /*<<< orphan*/  smnPerfMonCtrHi0 ; 
 int /*<<< orphan*/  smnPerfMonCtrHi1 ; 
 int /*<<< orphan*/  smnPerfMonCtrHi2 ; 
 int /*<<< orphan*/  smnPerfMonCtrHi3 ; 
 int /*<<< orphan*/  smnPerfMonCtrLo0 ; 
 int /*<<< orphan*/  smnPerfMonCtrLo1 ; 
 int /*<<< orphan*/  smnPerfMonCtrLo2 ; 
 int /*<<< orphan*/  smnPerfMonCtrLo3 ; 

__attribute__((used)) static void df_v3_6_pmc_get_addr(struct amdgpu_device *adev,
				 uint64_t config,
				 int is_ctrl,
				 uint32_t *lo_base_addr,
				 uint32_t *hi_base_addr)
{
	int target_cntr = df_v3_6_pmc_config_2_cntr(adev, config);

	if (target_cntr < 0)
		return;

	switch (target_cntr) {

	case 0:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo0 : smnPerfMonCtrLo0;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi0 : smnPerfMonCtrHi0;
		break;
	case 1:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo1 : smnPerfMonCtrLo1;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi1 : smnPerfMonCtrHi1;
		break;
	case 2:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo2 : smnPerfMonCtrLo2;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi2 : smnPerfMonCtrHi2;
		break;
	case 3:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo3 : smnPerfMonCtrLo3;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi3 : smnPerfMonCtrHi3;
		break;

	}

}