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
struct bfa_fcport_s {int /*<<< orphan*/  fec_state; int /*<<< orphan*/  topology; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FEC_OFFLINE ; 
 int /*<<< orphan*/  BFA_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_NONE ; 

__attribute__((used)) static void
bfa_fcport_reset_linkinfo(struct bfa_fcport_s *fcport)
{
	fcport->speed = BFA_PORT_SPEED_UNKNOWN;
	fcport->topology = BFA_PORT_TOPOLOGY_NONE;
	fcport->fec_state = BFA_FEC_OFFLINE;
}