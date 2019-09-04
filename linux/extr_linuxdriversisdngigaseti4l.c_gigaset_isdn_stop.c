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
struct cardstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  ISDN_STAT_STOP ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_i4l_cmd (struct cardstate*,int /*<<< orphan*/ ) ; 

void gigaset_isdn_stop(struct cardstate *cs)
{
	gig_dbg(DEBUG_CMD, "sending STOP");
	gigaset_i4l_cmd(cs, ISDN_STAT_STOP);
}