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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct truly_nt35597 {int /*<<< orphan*/  dev; int /*<<< orphan*/ * dsi; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int) ; 
 int mipi_dsi_dcs_write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct truly_nt35597* panel_to_ctx (struct drm_panel*) ; 

__attribute__((used)) static int truly_dcs_write_buf(struct drm_panel *panel,
	u32 size, const u8 *buf)
{
	struct truly_nt35597 *ctx = panel_to_ctx(panel);
	int ret = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(ctx->dsi); i++) {
		ret = mipi_dsi_dcs_write_buffer(ctx->dsi[i], buf, size);
		if (ret < 0) {
			DRM_DEV_ERROR(ctx->dev,
				"failed to tx cmd [%d], err: %d\n", i, ret);
			return ret;
		}
	}

	return ret;
}