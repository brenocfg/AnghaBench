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
typedef  int /*<<< orphan*/  uint16_t ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_SYM1 ; 
 int /*<<< orphan*/  DPHY_SYM2 ; 
 int /*<<< orphan*/  DPHY_SYM3 ; 
 int /*<<< orphan*/  DPHY_SYM4 ; 
 int /*<<< orphan*/  DPHY_SYM5 ; 
 int /*<<< orphan*/  DPHY_SYM6 ; 
 int /*<<< orphan*/  DPHY_SYM7 ; 
 int /*<<< orphan*/  DPHY_SYM8 ; 
 int /*<<< orphan*/  DP_DPHY_SYM0 ; 
 int /*<<< orphan*/  DP_DPHY_SYM1 ; 
 int /*<<< orphan*/  DP_DPHY_SYM2 ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_pattern_symbols(
	struct dcn10_link_encoder *enc10,
	uint16_t pattern_symbols[8])
{
	/* This register resides in DP back end block;
	 * transmitter is used for the offset
	 */
	REG_SET_3(DP_DPHY_SYM0, 0,
			DPHY_SYM1, pattern_symbols[0],
			DPHY_SYM2, pattern_symbols[1],
			DPHY_SYM3, pattern_symbols[2]);

	/* This register resides in DP back end block;
	 * transmitter is used for the offset
	 */
	REG_SET_3(DP_DPHY_SYM1, 0,
			DPHY_SYM4, pattern_symbols[3],
			DPHY_SYM5, pattern_symbols[4],
			DPHY_SYM6, pattern_symbols[5]);

	/* This register resides in DP back end block;
	 * transmitter is used for the offset
	 */
	REG_SET_2(DP_DPHY_SYM2, 0,
			DPHY_SYM7, pattern_symbols[6],
			DPHY_SYM8, pattern_symbols[7]);
}