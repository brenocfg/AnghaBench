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
typedef  int uint16_t ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_prbs_symbols (struct dcn10_link_encoder*,int) ; 
 int /*<<< orphan*/  enable_phy_bypass_mode (struct dcn10_link_encoder*,int) ; 
 int /*<<< orphan*/  program_pattern_symbols (struct dcn10_link_encoder*,int*) ; 

__attribute__((used)) static void set_dp_phy_pattern_80bit_custom(
	struct dcn10_link_encoder *enc10,
	const uint8_t *pattern)
{
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* Enable debug symbols on the lanes */

	disable_prbs_symbols(enc10, true);

	/* Enable PHY bypass mode to enable the test pattern */
	/* TODO is it really needed ? */

	enable_phy_bypass_mode(enc10, true);

	/* Program 80 bit custom pattern */
	{
		uint16_t pattern_symbols[8];

		pattern_symbols[0] =
			((pattern[1] & 0x03) << 8) | pattern[0];
		pattern_symbols[1] =
			((pattern[2] & 0x0f) << 6) | ((pattern[1] >> 2) & 0x3f);
		pattern_symbols[2] =
			((pattern[3] & 0x3f) << 4) | ((pattern[2] >> 4) & 0x0f);
		pattern_symbols[3] =
			(pattern[4] << 2) | ((pattern[3] >> 6) & 0x03);
		pattern_symbols[4] =
			((pattern[6] & 0x03) << 8) | pattern[5];
		pattern_symbols[5] =
			((pattern[7] & 0x0f) << 6) | ((pattern[6] >> 2) & 0x3f);
		pattern_symbols[6] =
			((pattern[8] & 0x3f) << 4) | ((pattern[7] >> 4) & 0x0f);
		pattern_symbols[7] =
			(pattern[9] << 2) | ((pattern[8] >> 6) & 0x03);

		program_pattern_symbols(enc10, pattern_symbols);
	}

	/* Enable phy bypass mode to enable the test pattern */

	enable_phy_bypass_mode(enc10, true);
}