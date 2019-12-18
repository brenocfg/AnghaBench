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
struct fc_rport {scalar_t__ port_state; int flags; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 scalar_t__ FC_PORTSTATE_ONLINE ; 
 int FC_RPORT_FAST_FAIL_TIMEDOUT ; 

__attribute__((used)) static blk_status_t fc_bsg_rport_prep(struct fc_rport *rport)
{
	if (rport->port_state == FC_PORTSTATE_BLOCKED &&
	    !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT))
		return BLK_STS_RESOURCE;

	if (rport->port_state != FC_PORTSTATE_ONLINE)
		return BLK_STS_IOERR;

	return BLK_STS_OK;
}