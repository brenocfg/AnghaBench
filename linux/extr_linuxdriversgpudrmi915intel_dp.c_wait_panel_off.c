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
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  IDLE_OFF_MASK ; 
 int /*<<< orphan*/  IDLE_OFF_VALUE ; 
 int /*<<< orphan*/  wait_panel_status (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_panel_off(struct intel_dp *intel_dp)
{
	DRM_DEBUG_KMS("Wait for panel power off time\n");
	wait_panel_status(intel_dp, IDLE_OFF_MASK, IDLE_OFF_VALUE);
}