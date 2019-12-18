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
 int /*<<< orphan*/  ATOM_EXT_PLL1 ; 
 int /*<<< orphan*/  ATOM_PPLL0 ; 
 int /*<<< orphan*/  ATOM_PPLL1 ; 
 int /*<<< orphan*/  ATOM_PPLL2 ; 
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
#define  CLOCK_SOURCE_ID_DFS 135 
#define  CLOCK_SOURCE_ID_DP_DTO 134 
#define  CLOCK_SOURCE_ID_EXTERNAL 133 
#define  CLOCK_SOURCE_ID_PLL0 132 
#define  CLOCK_SOURCE_ID_PLL1 131 
#define  CLOCK_SOURCE_ID_PLL2 130 
#define  CLOCK_SOURCE_ID_UNDEFINED 129 
#define  CLOCK_SOURCE_ID_VCE 128 

__attribute__((used)) static bool clock_source_id_to_atom(
	enum clock_source_id id,
	uint32_t *atom_pll_id)
{
	bool result = true;

	if (atom_pll_id != NULL)
		switch (id) {
		case CLOCK_SOURCE_ID_PLL0:
			*atom_pll_id = ATOM_PPLL0;
			break;
		case CLOCK_SOURCE_ID_PLL1:
			*atom_pll_id = ATOM_PPLL1;
			break;
		case CLOCK_SOURCE_ID_PLL2:
			*atom_pll_id = ATOM_PPLL2;
			break;
		case CLOCK_SOURCE_ID_EXTERNAL:
			*atom_pll_id = ATOM_PPLL_INVALID;
			break;
		case CLOCK_SOURCE_ID_DFS:
			*atom_pll_id = ATOM_EXT_PLL1;
			break;
		case CLOCK_SOURCE_ID_VCE:
			/* for VCE encoding,
			 * we need to pass in ATOM_PPLL_INVALID
			 */
			*atom_pll_id = ATOM_PPLL_INVALID;
			break;
		case CLOCK_SOURCE_ID_DP_DTO:
			/* When programming DP DTO PLL ID should be invalid */
			*atom_pll_id = ATOM_PPLL_INVALID;
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