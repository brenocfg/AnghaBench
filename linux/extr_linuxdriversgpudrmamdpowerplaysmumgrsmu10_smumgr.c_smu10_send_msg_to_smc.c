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
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP1 ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMP1_SMN_C2PMSG_90 ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu10_send_msg_to_smc_without_waiting (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 scalar_t__ smu10_wait_for_response (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu10_send_msg_to_smc(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	struct amdgpu_device *adev = hwmgr->adev;

	smu10_wait_for_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	smu10_send_msg_to_smc_without_waiting(hwmgr, msg);

	if (smu10_wait_for_response(hwmgr) == 0)
		printk("Failed to send Message %x.\n", msg);

	return 0;
}