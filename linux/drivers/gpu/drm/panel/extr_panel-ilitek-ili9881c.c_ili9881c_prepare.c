#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ cmd; int /*<<< orphan*/  page; } ;
struct ili9881c_instr {scalar_t__ op; TYPE_2__ arg; } ;
struct ili9881c {int /*<<< orphan*/  dsi; int /*<<< orphan*/  reset; int /*<<< orphan*/  power; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ili9881c_instr*) ; 
 scalar_t__ ILI9881C_COMMAND ; 
 scalar_t__ ILI9881C_SWITCH_PAGE ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_TEAR_MODE_VBLANK ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ili9881c_instr* ili9881c_init ; 
 int ili9881c_send_cmd_data (struct ili9881c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ili9881c_switch_page (struct ili9881c*,int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_exit_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_tear_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ili9881c* panel_to_ili9881c (struct drm_panel*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ili9881c_prepare(struct drm_panel *panel)
{
	struct ili9881c *ctx = panel_to_ili9881c(panel);
	unsigned int i;
	int ret;

	/* Power the panel */
	ret = regulator_enable(ctx->power);
	if (ret)
		return ret;
	msleep(5);

	/* And reset it */
	gpiod_set_value(ctx->reset, 1);
	msleep(20);

	gpiod_set_value(ctx->reset, 0);
	msleep(20);

	for (i = 0; i < ARRAY_SIZE(ili9881c_init); i++) {
		const struct ili9881c_instr *instr = &ili9881c_init[i];

		if (instr->op == ILI9881C_SWITCH_PAGE)
			ret = ili9881c_switch_page(ctx, instr->arg.page);
		else if (instr->op == ILI9881C_COMMAND)
			ret = ili9881c_send_cmd_data(ctx, instr->arg.cmd.cmd,
						      instr->arg.cmd.data);

		if (ret)
			return ret;
	}

	ret = ili9881c_switch_page(ctx, 0);
	if (ret)
		return ret;

	ret = mipi_dsi_dcs_set_tear_on(ctx->dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret)
		return ret;

	ret = mipi_dsi_dcs_exit_sleep_mode(ctx->dsi);
	if (ret)
		return ret;

	return 0;
}