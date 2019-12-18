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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_ALTVDDNB_NOTIFY ; 
 int /*<<< orphan*/  SUMO_SMU_SERVICE_ROUTINE_ALTVDDNB_NOTIFY ; 
 int /*<<< orphan*/  WREG32_RCU (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sumo_is_alt_vddnb_supported (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_send_msg_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 

void sumo_smu_notify_alt_vddnb_change(struct radeon_device *rdev,
				      bool powersaving, bool force_nbps1)
{
	u32 param = 0;

	if (!sumo_is_alt_vddnb_supported(rdev))
		return;

	if (powersaving)
		param |= 1;

	if (force_nbps1)
		param |= 2;

	WREG32_RCU(RCU_ALTVDDNB_NOTIFY, param);

	sumo_send_msg_to_smu(rdev, SUMO_SMU_SERVICE_ROUTINE_ALTVDDNB_NOTIFY);
}