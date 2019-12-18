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
struct dcn10_link_encoder {int dummy; } ;
struct dc_link_settings {scalar_t__ lane_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_SCRAMBLER_ADVANCE ; 
 int /*<<< orphan*/  DP_CONFIG ; 
 int /*<<< orphan*/  DP_DPHY_SCRAM_CNTL ; 
 int /*<<< orphan*/  DP_UDI_LANES ; 
 scalar_t__ LANE_COUNT_ONE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void enc1_configure_encoder(
	struct dcn10_link_encoder *enc10,
	const struct dc_link_settings *link_settings)
{
	/* set number of lanes */
	REG_SET(DP_CONFIG, 0,
			DP_UDI_LANES, link_settings->lane_count - LANE_COUNT_ONE);

	/* setup scrambler */
	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_ADVANCE, 1);
}