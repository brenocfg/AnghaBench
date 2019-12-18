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
struct srp_rport {int state; int /*<<< orphan*/  mutex; } ;
typedef  enum srp_rport_state { ____Placeholder_srp_rport_state } srp_rport_state ;

/* Variables and functions */
 int EINVAL ; 
#define  SRP_RPORT_BLOCKED 131 
#define  SRP_RPORT_FAIL_FAST 130 
#define  SRP_RPORT_LOST 129 
#define  SRP_RPORT_RUNNING 128 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srp_rport_set_state(struct srp_rport *rport,
			       enum srp_rport_state new_state)
{
	enum srp_rport_state old_state = rport->state;

	lockdep_assert_held(&rport->mutex);

	switch (new_state) {
	case SRP_RPORT_RUNNING:
		switch (old_state) {
		case SRP_RPORT_LOST:
			goto invalid;
		default:
			break;
		}
		break;
	case SRP_RPORT_BLOCKED:
		switch (old_state) {
		case SRP_RPORT_RUNNING:
			break;
		default:
			goto invalid;
		}
		break;
	case SRP_RPORT_FAIL_FAST:
		switch (old_state) {
		case SRP_RPORT_LOST:
			goto invalid;
		default:
			break;
		}
		break;
	case SRP_RPORT_LOST:
		break;
	}
	rport->state = new_state;
	return 0;

invalid:
	return -EINVAL;
}