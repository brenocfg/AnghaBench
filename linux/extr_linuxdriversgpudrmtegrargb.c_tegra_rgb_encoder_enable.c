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
typedef  int u32 ;
struct tegra_rgb {int /*<<< orphan*/  dc; } ;
struct tegra_output {scalar_t__ panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_COM_PIN_OUTPUT_POLARITY (int) ; 
 int /*<<< orphan*/  DC_DISP_DATA_ENABLE_OPTIONS ; 
 int /*<<< orphan*/  DC_DISP_DISP_INTERFACE_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_SHIFT_CLOCK_OPTIONS ; 
 int DE_CONTROL_NORMAL ; 
 int DE_SELECT_ACTIVE ; 
 int DISP_ALIGNMENT_MSB ; 
 int DISP_DATA_FORMAT_DF1P1C ; 
 int DISP_ORDER_RED_BLUE ; 
 int LHS_OUTPUT_POLARITY_LOW ; 
 int LVS_OUTPUT_POLARITY_LOW ; 
 int SC0_H_QUALIFIER_NONE ; 
 int SC1_H_QUALIFIER_NONE ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  rgb_enable ; 
 int /*<<< orphan*/  tegra_dc_commit (int /*<<< orphan*/ ) ; 
 int tegra_dc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_write_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct tegra_rgb* to_rgb (struct tegra_output*) ; 

__attribute__((used)) static void tegra_rgb_encoder_enable(struct drm_encoder *encoder)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_rgb *rgb = to_rgb(output);
	u32 value;

	if (output->panel)
		drm_panel_prepare(output->panel);

	tegra_dc_write_regs(rgb->dc, rgb_enable, ARRAY_SIZE(rgb_enable));

	value = DE_SELECT_ACTIVE | DE_CONTROL_NORMAL;
	tegra_dc_writel(rgb->dc, value, DC_DISP_DATA_ENABLE_OPTIONS);

	/* XXX: parameterize? */
	value = tegra_dc_readl(rgb->dc, DC_COM_PIN_OUTPUT_POLARITY(1));
	value &= ~LVS_OUTPUT_POLARITY_LOW;
	value &= ~LHS_OUTPUT_POLARITY_LOW;
	tegra_dc_writel(rgb->dc, value, DC_COM_PIN_OUTPUT_POLARITY(1));

	/* XXX: parameterize? */
	value = DISP_DATA_FORMAT_DF1P1C | DISP_ALIGNMENT_MSB |
		DISP_ORDER_RED_BLUE;
	tegra_dc_writel(rgb->dc, value, DC_DISP_DISP_INTERFACE_CONTROL);

	/* XXX: parameterize? */
	value = SC0_H_QUALIFIER_NONE | SC1_H_QUALIFIER_NONE;
	tegra_dc_writel(rgb->dc, value, DC_DISP_SHIFT_CLOCK_OPTIONS);

	tegra_dc_commit(rgb->dc);

	if (output->panel)
		drm_panel_enable(output->panel);
}