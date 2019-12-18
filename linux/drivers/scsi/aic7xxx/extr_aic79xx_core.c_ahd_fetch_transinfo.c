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
typedef  int u_int ;
struct ahd_tmode_tstate {struct ahd_initiator_tinfo* transinfo; } ;
struct ahd_softc {struct ahd_tmode_tstate** enabled_targets; } ;
struct ahd_initiator_tinfo {int dummy; } ;

/* Variables and functions */

struct ahd_initiator_tinfo *
ahd_fetch_transinfo(struct ahd_softc *ahd, char channel, u_int our_id,
		    u_int remote_id, struct ahd_tmode_tstate **tstate)
{
	/*
	 * Transfer data structures are stored from the perspective
	 * of the target role.  Since the parameters for a connection
	 * in the initiator role to a given target are the same as
	 * when the roles are reversed, we pretend we are the target.
	 */
	if (channel == 'B')
		our_id += 8;
	*tstate = ahd->enabled_targets[our_id];
	return (&(*tstate)->transinfo[remote_id]);
}