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
struct se_cmd {int alua_nonop_delay; int /*<<< orphan*/  se_cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCF_ALUA_NON_OPTIMIZED ; 

__attribute__((used)) static inline void core_alua_state_nonoptimized(
	struct se_cmd *cmd,
	unsigned char *cdb,
	int nonop_delay_msecs)
{
	/*
	 * Set SCF_ALUA_NON_OPTIMIZED here, this value will be checked
	 * later to determine if processing of this cmd needs to be
	 * temporarily delayed for the Active/NonOptimized primary access state.
	 */
	cmd->se_cmd_flags |= SCF_ALUA_NON_OPTIMIZED;
	cmd->alua_nonop_delay = nonop_delay_msecs;
}