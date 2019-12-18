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
struct uwb_rc {int dummy; } ;
struct uwb_dbg_cmd_ie {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int uwb_rc_ie_rm (struct uwb_rc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_ie_rm(struct uwb_rc *rc, struct uwb_dbg_cmd_ie *ie_to_rm)
{
	return uwb_rc_ie_rm(rc, ie_to_rm->data[0]);
}