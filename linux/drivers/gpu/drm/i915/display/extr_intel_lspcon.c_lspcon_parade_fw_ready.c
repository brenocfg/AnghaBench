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
typedef  int u8 ;
struct drm_dp_aux {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  LSPCON_PARADE_AVI_IF_CTRL ; 
 int LSPCON_PARADE_AVI_IF_KICKOFF ; 
 scalar_t__ drm_dp_dpcd_read (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool lspcon_parade_fw_ready(struct drm_dp_aux *aux)
{
	u8 avi_if_ctrl;
	u8 retry;
	ssize_t ret;

	/* Check if LSPCON FW is ready for data */
	for (retry = 0; retry < 5; retry++) {
		if (retry)
			usleep_range(200, 300);

		ret = drm_dp_dpcd_read(aux, LSPCON_PARADE_AVI_IF_CTRL,
				       &avi_if_ctrl, 1);
		if (ret < 0) {
			DRM_ERROR("Failed to read AVI IF control\n");
			return false;
		}

		if ((avi_if_ctrl & LSPCON_PARADE_AVI_IF_KICKOFF) == 0)
			return true;
	}

	DRM_ERROR("Parade FW not ready to accept AVI IF\n");
	return false;
}