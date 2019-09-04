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
typedef  int uint8_t ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;

/* Variables and functions */
 int ATOM_TRANSMITTER_CONFIG_V5_P0PLL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_P1PLL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_P2PLL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SRC_EXT ; 
#define  CLOCK_SOURCE_ID_EXTERNAL 131 
#define  CLOCK_SOURCE_ID_PLL0 130 
#define  CLOCK_SOURCE_ID_PLL1 129 
#define  CLOCK_SOURCE_ID_PLL2 128 

__attribute__((used)) static uint8_t clock_source_id_to_atom_phy_clk_src_id(
		enum clock_source_id id)
{
	uint8_t atom_phy_clk_src_id = 0;

	switch (id) {
	case CLOCK_SOURCE_ID_PLL0:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P0PLL;
		break;
	case CLOCK_SOURCE_ID_PLL1:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P1PLL;
		break;
	case CLOCK_SOURCE_ID_PLL2:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P2PLL;
		break;
	case CLOCK_SOURCE_ID_EXTERNAL:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SRC_EXT;
		break;
	default:
		atom_phy_clk_src_id = ATOM_TRANSMITTER_CONFIG_V5_P1PLL;
		break;
	}

	return atom_phy_clk_src_id >> 2;
}