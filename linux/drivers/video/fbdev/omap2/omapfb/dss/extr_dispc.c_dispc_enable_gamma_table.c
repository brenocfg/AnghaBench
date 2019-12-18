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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 int /*<<< orphan*/  DSSWARN (char*) ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 

void dispc_enable_gamma_table(bool enable)
{
	/*
	 * This is partially implemented to support only disabling of
	 * the gamma table.
	 */
	if (enable) {
		DSSWARN("Gamma table enabling for TV not yet supported");
		return;
	}

	REG_FLD_MOD(DISPC_CONFIG, enable, 9, 9);
}