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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
typedef  enum sun6i_dsi_start_inst { ____Placeholder_sun6i_dsi_start_inst } sun6i_dsi_start_inst ;

/* Variables and functions */
 int DSI_INST_ID_DLY ; 
 int DSI_INST_ID_END ; 
 int DSI_INST_ID_HSC ; 
 int DSI_INST_ID_HSCEXIT ; 
 int DSI_INST_ID_HSD ; 
 int DSI_INST_ID_LP11 ; 
 int DSI_INST_ID_LPDT ; 
 int DSI_INST_ID_NOP ; 
 int DSI_INST_ID_TBA ; 
#define  DSI_START_HSC 131 
#define  DSI_START_HSD 130 
#define  DSI_START_LPRX 129 
#define  DSI_START_LPTX 128 
 int /*<<< orphan*/  SUN6I_DSI_INST_FUNC_LANE_CEN ; 
 int /*<<< orphan*/  SUN6I_DSI_INST_FUNC_REG (int) ; 
 int /*<<< orphan*/  SUN6I_DSI_INST_JUMP_SEL_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_abort (struct sun6i_dsi*) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_commit (struct sun6i_dsi*) ; 

__attribute__((used)) static int sun6i_dsi_start(struct sun6i_dsi *dsi,
			   enum sun6i_dsi_start_inst func)
{
	switch (func) {
	case DSI_START_LPTX:
		regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_LPDT));
		break;
	case DSI_START_LPRX:
		regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_DLY  << (4 * DSI_INST_ID_LPDT) |
			     DSI_INST_ID_TBA  << (4 * DSI_INST_ID_DLY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_TBA));
		break;
	case DSI_START_HSC:
		regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_HSC  << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSC));
		break;
	case DSI_START_HSD:
		regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_HSD  << (4 * DSI_INST_ID_NOP) |
			     DSI_INST_ID_DLY  << (4 * DSI_INST_ID_HSD) |
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_DLY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSCEXIT));
		break;
	default:
		regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_LP11));
		break;
	}

	sun6i_dsi_inst_abort(dsi);
	sun6i_dsi_inst_commit(dsi);

	if (func == DSI_START_HSC)
		regmap_write_bits(dsi->regs,
				  SUN6I_DSI_INST_FUNC_REG(DSI_INST_ID_LP11),
				  SUN6I_DSI_INST_FUNC_LANE_CEN, 0);

	return 0;
}