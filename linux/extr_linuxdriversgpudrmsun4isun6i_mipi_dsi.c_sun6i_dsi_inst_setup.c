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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
typedef  enum sun6i_dsi_inst_packet { ____Placeholder_sun6i_dsi_inst_packet } sun6i_dsi_inst_packet ;
typedef  enum sun6i_dsi_inst_mode { ____Placeholder_sun6i_dsi_inst_mode } sun6i_dsi_inst_mode ;
typedef  enum sun6i_dsi_inst_id { ____Placeholder_sun6i_dsi_inst_id } sun6i_dsi_inst_id ;
typedef  enum sun6i_dsi_inst_escape { ____Placeholder_sun6i_dsi_inst_escape } sun6i_dsi_inst_escape ;

/* Variables and functions */
 int SUN6I_DSI_INST_FUNC_ESCAPE_ENTRY (int) ; 
 int SUN6I_DSI_INST_FUNC_INST_MODE (int) ; 
 int SUN6I_DSI_INST_FUNC_LANE_CEN ; 
 int SUN6I_DSI_INST_FUNC_LANE_DEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_DSI_INST_FUNC_REG (int) ; 
 int SUN6I_DSI_INST_FUNC_TRANS_PACKET (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun6i_dsi_inst_setup(struct sun6i_dsi *dsi,
				 enum sun6i_dsi_inst_id id,
				 enum sun6i_dsi_inst_mode mode,
				 bool clock, u8 data,
				 enum sun6i_dsi_inst_packet packet,
				 enum sun6i_dsi_inst_escape escape)
{
	regmap_write(dsi->regs, SUN6I_DSI_INST_FUNC_REG(id),
		     SUN6I_DSI_INST_FUNC_INST_MODE(mode) |
		     SUN6I_DSI_INST_FUNC_ESCAPE_ENTRY(escape) |
		     SUN6I_DSI_INST_FUNC_TRANS_PACKET(packet) |
		     (clock ? SUN6I_DSI_INST_FUNC_LANE_CEN : 0) |
		     SUN6I_DSI_INST_FUNC_LANE_DEN(data));
}