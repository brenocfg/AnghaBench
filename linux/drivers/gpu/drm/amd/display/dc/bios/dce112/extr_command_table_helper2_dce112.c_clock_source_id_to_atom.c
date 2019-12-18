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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL0 ; 
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL1 ; 
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL2 ; 
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL3 ; 
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL4 ; 
 int /*<<< orphan*/  ATOM_COMBOPHY_PLL5 ; 
 int /*<<< orphan*/  ATOM_DP_DTO ; 
 int /*<<< orphan*/  ATOM_GCK_DFS ; 
 int /*<<< orphan*/  ATOM_PPLL0 ; 
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
#define  CLOCK_SOURCE_COMBO_DISPLAY_PLL0 138 
#define  CLOCK_SOURCE_COMBO_PHY_PLL0 137 
#define  CLOCK_SOURCE_COMBO_PHY_PLL1 136 
#define  CLOCK_SOURCE_COMBO_PHY_PLL2 135 
#define  CLOCK_SOURCE_COMBO_PHY_PLL3 134 
#define  CLOCK_SOURCE_COMBO_PHY_PLL4 133 
#define  CLOCK_SOURCE_COMBO_PHY_PLL5 132 
#define  CLOCK_SOURCE_ID_DFS 131 
#define  CLOCK_SOURCE_ID_DP_DTO 130 
#define  CLOCK_SOURCE_ID_UNDEFINED 129 
#define  CLOCK_SOURCE_ID_VCE 128 

__attribute__((used)) static bool clock_source_id_to_atom(
	enum clock_source_id id,
	uint32_t *atom_pll_id)
{
	bool result = true;

	if (atom_pll_id != NULL)
		switch (id) {
		case CLOCK_SOURCE_COMBO_PHY_PLL0:
			*atom_pll_id = ATOM_COMBOPHY_PLL0;
			break;
		case CLOCK_SOURCE_COMBO_PHY_PLL1:
			*atom_pll_id = ATOM_COMBOPHY_PLL1;
			break;
		case CLOCK_SOURCE_COMBO_PHY_PLL2:
			*atom_pll_id = ATOM_COMBOPHY_PLL2;
			break;
		case CLOCK_SOURCE_COMBO_PHY_PLL3:
			*atom_pll_id = ATOM_COMBOPHY_PLL3;
			break;
		case CLOCK_SOURCE_COMBO_PHY_PLL4:
			*atom_pll_id = ATOM_COMBOPHY_PLL4;
			break;
		case CLOCK_SOURCE_COMBO_PHY_PLL5:
			*atom_pll_id = ATOM_COMBOPHY_PLL5;
			break;
		case CLOCK_SOURCE_COMBO_DISPLAY_PLL0:
			*atom_pll_id = ATOM_PPLL0;
			break;
		case CLOCK_SOURCE_ID_DFS:
			*atom_pll_id = ATOM_GCK_DFS;
			break;
		case CLOCK_SOURCE_ID_VCE:
			*atom_pll_id = ATOM_DP_DTO;
			break;
		case CLOCK_SOURCE_ID_DP_DTO:
			*atom_pll_id = ATOM_DP_DTO;
			break;
		case CLOCK_SOURCE_ID_UNDEFINED:
			/* Should not happen */
			*atom_pll_id = ATOM_PPLL_INVALID;
			result = false;
			break;
		default:
			result = false;
			break;
		}

	return result;
}