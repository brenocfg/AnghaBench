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
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  SMU_MSG_AllowGfxOff ; 
 int /*<<< orphan*/  SMU_MSG_DisallowGfxOff ; 
 int /*<<< orphan*/  msleep (int) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_v12_0_get_gfxoff_status (struct smu_context*) ; 

__attribute__((used)) static int smu_v12_0_gfx_off_control(struct smu_context *smu, bool enable)
{
	int ret = 0, timeout = 500;

	if (enable) {
		ret = smu_send_smc_msg(smu, SMU_MSG_AllowGfxOff);

		/* confirm gfx is back to "off" state, timeout is 5 seconds */
		while (!(smu_v12_0_get_gfxoff_status(smu) == 0)) {
			msleep(10);
			timeout--;
			if (timeout == 0) {
				DRM_ERROR("enable gfxoff timeout and failed!\n");
				break;
			}
		}
	} else {
		ret = smu_send_smc_msg(smu, SMU_MSG_DisallowGfxOff);

		/* confirm gfx is back to "on" state, timeout is 0.5 second */
		while (!(smu_v12_0_get_gfxoff_status(smu) == 2)) {
			msleep(1);
			timeout--;
			if (timeout == 0) {
				DRM_ERROR("disable gfxoff timeout and failed!\n");
				break;
			}
		}
	}

	return ret;
}