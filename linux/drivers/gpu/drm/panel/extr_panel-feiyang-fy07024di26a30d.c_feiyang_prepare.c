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
struct mipi_dsi_device {int dummy; } ;
struct feiyang_init_cmd {int /*<<< orphan*/  data; } ;
struct feiyang {int /*<<< orphan*/  reset; int /*<<< orphan*/  avdd; int /*<<< orphan*/  dvdd; struct mipi_dsi_device* dsi; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct feiyang_init_cmd*) ; 
 int /*<<< orphan*/  FEIYANG_INIT_CMD_LEN ; 
 struct feiyang_init_cmd* feiyang_init_cmds ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_dcs_write_buffer (struct mipi_dsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct feiyang* panel_to_feiyang (struct drm_panel*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int feiyang_prepare(struct drm_panel *panel)
{
	struct feiyang *ctx = panel_to_feiyang(panel);
	struct mipi_dsi_device *dsi = ctx->dsi;
	unsigned int i;
	int ret;

	ret = regulator_enable(ctx->dvdd);
	if (ret)
		return ret;

	/* T1 (dvdd start + dvdd rise) 0 < T1 <= 10ms */
	msleep(10);

	ret = regulator_enable(ctx->avdd);
	if (ret)
		return ret;

	/* T3 (dvdd rise + avdd start + avdd rise) T3 >= 20ms */
	msleep(20);

	gpiod_set_value(ctx->reset, 0);

	/*
	 * T5 + T6 (avdd rise + video & logic signal rise)
	 * T5 >= 10ms, 0 < T6 <= 10ms
	 */
	msleep(20);

	gpiod_set_value(ctx->reset, 1);

	/* T12 (video & logic signal rise + backlight rise) T12 >= 200ms */
	msleep(200);

	for (i = 0; i < ARRAY_SIZE(feiyang_init_cmds); i++) {
		const struct feiyang_init_cmd *cmd =
						&feiyang_init_cmds[i];

		ret = mipi_dsi_dcs_write_buffer(dsi, cmd->data,
						FEIYANG_INIT_CMD_LEN);
		if (ret < 0)
			return ret;
	}

	return 0;
}