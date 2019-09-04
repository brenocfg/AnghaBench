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
struct panel_init_cmd {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct innolux_panel {int prepared; int /*<<< orphan*/  supplies; TYPE_1__* desc; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  link; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_supplies; struct panel_init_cmd* init_cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_dcs_exit_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_nop (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_on (int /*<<< orphan*/ ) ; 
 int mipi_dsi_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct innolux_panel* to_innolux_panel (struct drm_panel*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int innolux_panel_prepare(struct drm_panel *panel)
{
	struct innolux_panel *innolux = to_innolux_panel(panel);
	int err;

	if (innolux->prepared)
		return 0;

	gpiod_set_value_cansleep(innolux->enable_gpio, 0);

	err = regulator_bulk_enable(innolux->desc->num_supplies,
				    innolux->supplies);
	if (err < 0)
		return err;

	/* p079zca: t2 (20ms), p097pfg: t4 (15ms) */
	usleep_range(20000, 21000);

	gpiod_set_value_cansleep(innolux->enable_gpio, 1);

	/* p079zca: t4, p097pfg: t5 */
	usleep_range(20000, 21000);

	if (innolux->desc->init_cmds) {
		const struct panel_init_cmd *cmds =
					innolux->desc->init_cmds;
		unsigned int i;

		for (i = 0; cmds[i].len != 0; i++) {
			const struct panel_init_cmd *cmd = &cmds[i];

			err = mipi_dsi_generic_write(innolux->link, cmd->data,
						     cmd->len);
			if (err < 0) {
				dev_err(panel->dev,
					"failed to write command %u\n", i);
				goto poweroff;
			}

			/*
			 * Included by random guessing, because without this
			 * (or at least, some delay), the panel sometimes
			 * didn't appear to pick up the command sequence.
			 */
			err = mipi_dsi_dcs_nop(innolux->link);
			if (err < 0) {
				dev_err(panel->dev,
					"failed to send DCS nop: %d\n", err);
				goto poweroff;
			}
		}
	}

	err = mipi_dsi_dcs_exit_sleep_mode(innolux->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to exit sleep mode: %d\n",
			      err);
		goto poweroff;
	}

	/* T6: 120ms - 1000ms*/
	msleep(120);

	err = mipi_dsi_dcs_set_display_on(innolux->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to set display on: %d\n",
			      err);
		goto poweroff;
	}

	/* T7: 5ms */
	usleep_range(5000, 6000);

	innolux->prepared = true;

	return 0;

poweroff:
	gpiod_set_value_cansleep(innolux->enable_gpio, 0);
	regulator_bulk_disable(innolux->desc->num_supplies, innolux->supplies);

	return err;
}