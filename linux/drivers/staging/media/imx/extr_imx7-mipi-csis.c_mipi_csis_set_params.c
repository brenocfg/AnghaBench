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
typedef  int u32 ;
struct TYPE_3__ {int num_data_lanes; } ;
struct csi_state {scalar_t__ wrap_clk; TYPE_2__* csis_fmt; int /*<<< orphan*/  hs_settle; TYPE_1__ bus; } ;
struct TYPE_4__ {int data_alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_CSIS_CLK_CTRL ; 
 int MIPI_CSIS_CLK_CTRL_CLKGATE_EN_MSK ; 
 int MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH0 (int) ; 
 int MIPI_CSIS_CLK_CTRL_WCLK_SRC ; 
 int /*<<< orphan*/  MIPI_CSIS_CMN_CTRL ; 
 int MIPI_CSIS_CMN_CTRL_LANE_NR_MASK ; 
 int MIPI_CSIS_CMN_CTRL_LANE_NR_OFFSET ; 
 int MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW ; 
 int MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW_CTRL ; 
 int /*<<< orphan*/  MIPI_CSIS_DPHYBCTRL_H ; 
 int /*<<< orphan*/  MIPI_CSIS_DPHYBCTRL_L ; 
 int MIPI_CSIS_ISPCFG_ALIGN_32BIT ; 
 int /*<<< orphan*/  MIPI_CSIS_ISPCONFIG_CH0 ; 
 int /*<<< orphan*/  MIPI_CSIS_ISPSYNC_CH0 ; 
 int MIPI_CSIS_ISPSYNC_HSYNC_LINTV_OFFSET ; 
 int MIPI_CSIS_ISPSYNC_VSYNC_EINTV_OFFSET ; 
 int MIPI_CSIS_ISPSYNC_VSYNC_SINTV_OFFSET ; 
 int /*<<< orphan*/  __mipi_csis_set_format (struct csi_state*) ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_set_hsync_settle (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mipi_csis_set_params(struct csi_state *state)
{
	int lanes = state->bus.num_data_lanes;
	u32 val;

	val = mipi_csis_read(state, MIPI_CSIS_CMN_CTRL);
	val &= ~MIPI_CSIS_CMN_CTRL_LANE_NR_MASK;
	val |= (lanes - 1) << MIPI_CSIS_CMN_CTRL_LANE_NR_OFFSET;
	mipi_csis_write(state, MIPI_CSIS_CMN_CTRL, val);

	__mipi_csis_set_format(state);

	mipi_csis_set_hsync_settle(state, state->hs_settle);

	val = mipi_csis_read(state, MIPI_CSIS_ISPCONFIG_CH0);
	if (state->csis_fmt->data_alignment == 32)
		val |= MIPI_CSIS_ISPCFG_ALIGN_32BIT;
	else
		val &= ~MIPI_CSIS_ISPCFG_ALIGN_32BIT;
	mipi_csis_write(state, MIPI_CSIS_ISPCONFIG_CH0, val);

	val = (0 << MIPI_CSIS_ISPSYNC_HSYNC_LINTV_OFFSET) |
		(0 << MIPI_CSIS_ISPSYNC_VSYNC_SINTV_OFFSET) |
		(0 << MIPI_CSIS_ISPSYNC_VSYNC_EINTV_OFFSET);
	mipi_csis_write(state, MIPI_CSIS_ISPSYNC_CH0, val);

	val = mipi_csis_read(state, MIPI_CSIS_CLK_CTRL);
	val &= ~MIPI_CSIS_CLK_CTRL_WCLK_SRC;
	if (state->wrap_clk)
		val |= MIPI_CSIS_CLK_CTRL_WCLK_SRC;
	else
		val &= ~MIPI_CSIS_CLK_CTRL_WCLK_SRC;

	val |= MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH0(15);
	val &= ~MIPI_CSIS_CLK_CTRL_CLKGATE_EN_MSK;
	mipi_csis_write(state, MIPI_CSIS_CLK_CTRL, val);

	mipi_csis_write(state, MIPI_CSIS_DPHYBCTRL_L, 0x1f4);
	mipi_csis_write(state, MIPI_CSIS_DPHYBCTRL_H, 0);

	/* Update the shadow register. */
	val = mipi_csis_read(state, MIPI_CSIS_CMN_CTRL);
	mipi_csis_write(state, MIPI_CSIS_CMN_CTRL,
			val | MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW |
			MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW_CTRL);
}