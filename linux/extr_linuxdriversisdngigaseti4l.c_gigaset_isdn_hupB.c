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
struct bc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  ISDN_STAT_BHUP ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_i4l_channel_cmd (struct bc_state*,int /*<<< orphan*/ ) ; 

void gigaset_isdn_hupB(struct bc_state *bcs)
{
	gig_dbg(DEBUG_CMD, "sending BHUP");
	gigaset_i4l_channel_cmd(bcs, ISDN_STAT_BHUP);
}