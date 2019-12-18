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
typedef  int u32 ;
struct sti_dvo {int enabled; scalar_t__ regs; int /*<<< orphan*/  panel; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_pix; struct dvo_config* config; } ;
struct dvo_config {int lowbyte; int midbyte; int highbyte; int flags; scalar_t__ awg_fwgen_fct; } ;
struct drm_bridge {struct sti_dvo* driver_private; } ;

/* Variables and functions */
 int AWG_MAX_INST ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ DVO_AWG_DIGSYNC_CTRL ; 
 scalar_t__ DVO_DOF_CFG ; 
 int DVO_DOF_EN ; 
 scalar_t__ DVO_LUT_PROG_HIGH ; 
 scalar_t__ DVO_LUT_PROG_LOW ; 
 scalar_t__ DVO_LUT_PROG_MID ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvo_awg_configure (struct sti_dvo*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvo_awg_generate_code (struct sti_dvo*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sti_dvo_pre_enable(struct drm_bridge *bridge)
{
	struct sti_dvo *dvo = bridge->driver_private;
	struct dvo_config *config = dvo->config;
	u32 val;

	DRM_DEBUG_DRIVER("\n");

	if (dvo->enabled)
		return;

	/* Make sure DVO is disabled */
	writel(0x00000000, dvo->regs + DVO_DOF_CFG);
	writel(0x00000000, dvo->regs + DVO_AWG_DIGSYNC_CTRL);

	if (config->awg_fwgen_fct) {
		u8 nb_instr;
		u32 awg_ram_code[AWG_MAX_INST];
		/* Configure AWG */
		if (!dvo_awg_generate_code(dvo, &nb_instr, awg_ram_code))
			dvo_awg_configure(dvo, awg_ram_code, nb_instr);
		else
			return;
	}

	/* Prepare/enable clocks */
	if (clk_prepare_enable(dvo->clk_pix))
		DRM_ERROR("Failed to prepare/enable dvo_pix clk\n");
	if (clk_prepare_enable(dvo->clk))
		DRM_ERROR("Failed to prepare/enable dvo clk\n");

	drm_panel_enable(dvo->panel);

	/* Set LUT */
	writel(config->lowbyte,  dvo->regs + DVO_LUT_PROG_LOW);
	writel(config->midbyte,  dvo->regs + DVO_LUT_PROG_MID);
	writel(config->highbyte, dvo->regs + DVO_LUT_PROG_HIGH);

	/* Digital output formatter config */
	val = (config->flags | DVO_DOF_EN);
	writel(val, dvo->regs + DVO_DOF_CFG);

	dvo->enabled = true;
}