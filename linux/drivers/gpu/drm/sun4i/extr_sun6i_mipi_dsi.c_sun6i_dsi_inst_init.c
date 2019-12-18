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
typedef  int u8 ;
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
struct mipi_dsi_device {scalar_t__ lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_INST_ESCA_LPDT ; 
 int /*<<< orphan*/  DSI_INST_ID_DLY ; 
 int /*<<< orphan*/  DSI_INST_ID_HSC ; 
 int /*<<< orphan*/  DSI_INST_ID_HSCEXIT ; 
 int /*<<< orphan*/  DSI_INST_ID_HSD ; 
 int /*<<< orphan*/  DSI_INST_ID_LP11 ; 
 int /*<<< orphan*/  DSI_INST_ID_LPDT ; 
 int /*<<< orphan*/  DSI_INST_ID_NOP ; 
 int /*<<< orphan*/  DSI_INST_ID_TBA ; 
 int /*<<< orphan*/  DSI_INST_MODE_ESCAPE ; 
 int /*<<< orphan*/  DSI_INST_MODE_HS ; 
 int /*<<< orphan*/  DSI_INST_MODE_HSCEXIT ; 
 int /*<<< orphan*/  DSI_INST_MODE_NOP ; 
 int /*<<< orphan*/  DSI_INST_MODE_STOP ; 
 int /*<<< orphan*/  DSI_INST_MODE_TBA ; 
 int /*<<< orphan*/  DSI_INST_PACK_COMMAND ; 
 int /*<<< orphan*/  DSI_INST_PACK_PIXEL ; 
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int SUN6I_DSI_INST_JUMP_CFG_NUM (int) ; 
 int SUN6I_DSI_INST_JUMP_CFG_POINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_DSI_INST_JUMP_CFG_REG (int /*<<< orphan*/ ) ; 
 int SUN6I_DSI_INST_JUMP_CFG_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_setup (struct sun6i_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_dsi_inst_init(struct sun6i_dsi *dsi,
				struct mipi_dsi_device *device)
{
	u8 lanes_mask = GENMASK(device->lanes - 1, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_LP11, DSI_INST_MODE_STOP,
			     true, lanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_TBA, DSI_INST_MODE_TBA,
			     false, 1, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSC, DSI_INST_MODE_HS,
			     true, 0, DSI_INST_PACK_PIXEL, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSD, DSI_INST_MODE_HS,
			     false, lanes_mask, DSI_INST_PACK_PIXEL, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_LPDT, DSI_INST_MODE_ESCAPE,
			     false, 1, DSI_INST_PACK_COMMAND,
			     DSI_INST_ESCA_LPDT);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSCEXIT, DSI_INST_MODE_HSCEXIT,
			     true, 0, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_NOP, DSI_INST_MODE_STOP,
			     false, lanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_DLY, DSI_INST_MODE_NOP,
			     true, lanes_mask, 0, 0);

	regmap_write(dsi->regs, SUN6I_DSI_INST_JUMP_CFG_REG(0),
		     SUN6I_DSI_INST_JUMP_CFG_POINT(DSI_INST_ID_NOP) |
		     SUN6I_DSI_INST_JUMP_CFG_TO(DSI_INST_ID_HSCEXIT) |
		     SUN6I_DSI_INST_JUMP_CFG_NUM(1));
}