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
struct cardstate {int /*<<< orphan*/ * iif; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  ISDN_STAT_UNLOAD ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_i4l_cmd (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void gigaset_isdn_unregdev(struct cardstate *cs)
{
	gig_dbg(DEBUG_CMD, "sending UNLOAD");
	gigaset_i4l_cmd(cs, ISDN_STAT_UNLOAD);
	kfree(cs->iif);
	cs->iif = NULL;
}