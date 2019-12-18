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
struct TYPE_2__ {int speed; } ;
struct bfa_rport_s {TYPE_1__ rport_info; } ;
typedef  enum bfa_port_speed { ____Placeholder_bfa_port_speed } bfa_port_speed ;

/* Variables and functions */
 int BFA_PORT_SPEED_AUTO ; 
 int /*<<< orphan*/  BFA_RPORT_SM_SET_SPEED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 

void
bfa_rport_speed(struct bfa_rport_s *rport, enum bfa_port_speed speed)
{
	WARN_ON(speed == 0);
	WARN_ON(speed == BFA_PORT_SPEED_AUTO);

	if (rport) {
		rport->rport_info.speed = speed;
		bfa_sm_send_event(rport, BFA_RPORT_SM_SET_SPEED);
	}
}