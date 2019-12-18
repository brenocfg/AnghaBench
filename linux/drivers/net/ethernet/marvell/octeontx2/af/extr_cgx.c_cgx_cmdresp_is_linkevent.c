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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 scalar_t__ CGX_CMD_LINK_BRING_DOWN ; 
 scalar_t__ CGX_CMD_LINK_BRING_UP ; 
 int /*<<< orphan*/  EVTREG_ID ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool cgx_cmdresp_is_linkevent(u64 event)
{
	u8 id;

	id = FIELD_GET(EVTREG_ID, event);
	if (id == CGX_CMD_LINK_BRING_UP ||
	    id == CGX_CMD_LINK_BRING_DOWN)
		return true;
	else
		return false;
}