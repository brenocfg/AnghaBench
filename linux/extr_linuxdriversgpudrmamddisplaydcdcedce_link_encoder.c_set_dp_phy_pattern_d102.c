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
typedef  int uint16_t ;
struct dce110_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_prbs_mode (struct dce110_link_encoder*) ; 
 int /*<<< orphan*/  disable_prbs_symbols (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  enable_phy_bypass_mode (struct dce110_link_encoder*,int) ; 
 int /*<<< orphan*/  program_pattern_symbols (struct dce110_link_encoder*,int*) ; 

__attribute__((used)) static void set_dp_phy_pattern_d102(
	struct dce110_link_encoder *enc110)
{
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc110, false);

	/* For 10-bit PRBS or debug symbols
	 * please use the following sequence: */

	/* Enable debug symbols on the lanes */

	disable_prbs_symbols(enc110, true);

	/* Disable PRBS mode */
	disable_prbs_mode(enc110);

	/* Program debug symbols to be output */
	{
		uint16_t pattern_symbols[8] = {
			0x2AA, 0x2AA, 0x2AA, 0x2AA,
			0x2AA, 0x2AA, 0x2AA, 0x2AA
		};

		program_pattern_symbols(enc110, pattern_symbols);
	}

	/* Enable phy bypass mode to enable the test pattern */

	enable_phy_bypass_mode(enc110, true);
}