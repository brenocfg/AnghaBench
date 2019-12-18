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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_SEQ_ASSERT_RESET ; 
 int /*<<< orphan*/  MIPI_SEQ_DISPLAY_OFF ; 
 int /*<<< orphan*/  MIPI_SEQ_POWER_OFF ; 
 struct intel_dsi* enc_to_intel_dsi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dsi_vbt_exec_sequence (struct intel_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_cmds_dispatched_to_panel (struct intel_encoder*) ; 

__attribute__((used)) static void gen11_dsi_powerdown_panel(struct intel_encoder *encoder)
{
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);

	intel_dsi_vbt_exec_sequence(intel_dsi, MIPI_SEQ_DISPLAY_OFF);
	intel_dsi_vbt_exec_sequence(intel_dsi, MIPI_SEQ_ASSERT_RESET);
	intel_dsi_vbt_exec_sequence(intel_dsi, MIPI_SEQ_POWER_OFF);

	/* ensure cmds dispatched to panel */
	wait_for_cmds_dispatched_to_panel(encoder);
}