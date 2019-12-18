#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_MGR_FLD_GO ; 
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dispc_mgr_go_busy (int) ; 
 int /*<<< orphan*/  dispc_mgr_is_enabled (int) ; 
 TYPE_1__* mgr_desc ; 
 int /*<<< orphan*/  mgr_fld_write (int,int /*<<< orphan*/ ,int) ; 

void dispc_mgr_go(enum omap_channel channel)
{
	WARN_ON(!dispc_mgr_is_enabled(channel));
	WARN_ON(dispc_mgr_go_busy(channel));

	DSSDBG("GO %s\n", mgr_desc[channel].name);

	mgr_fld_write(channel, DISPC_MGR_FLD_GO, 1);
}