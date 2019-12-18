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
struct tegra_rgb {int /*<<< orphan*/  dc; } ;
struct tegra_output {scalar_t__ panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  rgb_disable ; 
 int /*<<< orphan*/  tegra_dc_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_write_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_rgb* to_rgb (struct tegra_output*) ; 

__attribute__((used)) static void tegra_rgb_encoder_disable(struct drm_encoder *encoder)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_rgb *rgb = to_rgb(output);

	if (output->panel)
		drm_panel_disable(output->panel);

	tegra_dc_write_regs(rgb->dc, rgb_disable, ARRAY_SIZE(rgb_disable));
	tegra_dc_commit(rgb->dc);

	if (output->panel)
		drm_panel_unprepare(output->panel);
}