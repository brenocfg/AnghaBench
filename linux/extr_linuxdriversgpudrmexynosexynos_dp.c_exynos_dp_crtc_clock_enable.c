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
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct exynos_dp_device {struct drm_encoder encoder; } ;
struct analogix_dp_plat_data {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  exynos_drm_pipe_clk_enable (int /*<<< orphan*/ ,int) ; 
 struct exynos_dp_device* to_dp (struct analogix_dp_plat_data*) ; 
 int /*<<< orphan*/  to_exynos_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dp_crtc_clock_enable(struct analogix_dp_plat_data *plat_data,
				bool enable)
{
	struct exynos_dp_device *dp = to_dp(plat_data);
	struct drm_encoder *encoder = &dp->encoder;

	if (!encoder->crtc)
		return -EPERM;

	exynos_drm_pipe_clk_enable(to_exynos_crtc(encoder->crtc), enable);

	return 0;
}