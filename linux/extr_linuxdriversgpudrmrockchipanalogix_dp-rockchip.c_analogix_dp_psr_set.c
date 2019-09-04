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
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct rockchip_dp_device {int /*<<< orphan*/  adp; int /*<<< orphan*/  dev; TYPE_1__ encoder; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PSR_WAIT_LINE_FLAG_TIMEOUT_MS ; 
 int analogix_dp_disable_psr (int /*<<< orphan*/ ) ; 
 int analogix_dp_enable_psr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_psr_enabled (int /*<<< orphan*/ ) ; 
 int rockchip_drm_wait_vact_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rockchip_dp_device* to_dp (struct drm_encoder*) ; 

__attribute__((used)) static int analogix_dp_psr_set(struct drm_encoder *encoder, bool enabled)
{
	struct rockchip_dp_device *dp = to_dp(encoder);
	int ret;

	if (!analogix_dp_psr_enabled(dp->adp))
		return 0;

	DRM_DEV_DEBUG(dp->dev, "%s PSR...\n", enabled ? "Entry" : "Exit");

	ret = rockchip_drm_wait_vact_end(dp->encoder.crtc,
					 PSR_WAIT_LINE_FLAG_TIMEOUT_MS);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "line flag interrupt did not arrive\n");
		return -ETIMEDOUT;
	}

	if (enabled)
		return analogix_dp_enable_psr(dp->adp);
	else
		return analogix_dp_disable_psr(dp->adp);
}