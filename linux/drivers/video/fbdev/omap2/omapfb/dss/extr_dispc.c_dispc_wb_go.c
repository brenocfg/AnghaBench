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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONTROL2 ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int REG_GET (int /*<<< orphan*/ ,int,int) ; 

void dispc_wb_go(void)
{
	enum omap_plane plane = OMAP_DSS_WB;
	bool enable, go;

	enable = REG_GET(DISPC_OVL_ATTRIBUTES(plane), 0, 0) == 1;

	if (!enable)
		return;

	go = REG_GET(DISPC_CONTROL2, 6, 6) == 1;
	if (go) {
		DSSERR("GO bit not down for WB\n");
		return;
	}

	REG_FLD_MOD(DISPC_CONTROL2, 1, 6, 6);
}