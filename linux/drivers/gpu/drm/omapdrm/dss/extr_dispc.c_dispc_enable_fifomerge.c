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
struct dispc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 int /*<<< orphan*/  DSSDBG (char*,char*) ; 
 int /*<<< orphan*/  FEAT_FIFO_MERGE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 

void dispc_enable_fifomerge(struct dispc_device *dispc, bool enable)
{
	if (!dispc_has_feature(dispc, FEAT_FIFO_MERGE)) {
		WARN_ON(enable);
		return;
	}

	DSSDBG("FIFO merge %s\n", enable ? "enabled" : "disabled");
	REG_FLD_MOD(dispc, DISPC_CONFIG, enable ? 1 : 0, 14, 14);
}