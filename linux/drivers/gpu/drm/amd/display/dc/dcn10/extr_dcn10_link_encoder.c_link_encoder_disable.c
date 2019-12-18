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

/* Variables and functions */
 int /*<<< orphan*/  DPHY_TRAINING_PATTERN_SEL ; 
 int /*<<< orphan*/  DP_DPHY_TRAINING_PATTERN_SEL ; 
 int /*<<< orphan*/  DP_LINK_CNTL ; 
 int /*<<< orphan*/  DP_LINK_TRAINING_COMPLETE ; 
 int /*<<< orphan*/  DP_PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_panel_mode (struct dcn10_link_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_encoder_disable(struct dcn10_link_encoder *enc10)
{
	/* reset training pattern */
	REG_SET(DP_DPHY_TRAINING_PATTERN_SEL, 0,
			DPHY_TRAINING_PATTERN_SEL, 0);

	/* reset training complete */
	REG_UPDATE(DP_LINK_CNTL, DP_LINK_TRAINING_COMPLETE, 0);

	/* reset panel mode */
	setup_panel_mode(enc10, DP_PANEL_MODE_DEFAULT);
}