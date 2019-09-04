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
struct srpt_send_ioctx {int state; } ;
typedef  enum srpt_command_state { ____Placeholder_srpt_command_state } srpt_command_state ;

/* Variables and functions */
 int SRPT_STATE_DONE ; 
 int SRPT_STATE_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static bool srpt_test_and_set_cmd_state(struct srpt_send_ioctx *ioctx,
					enum srpt_command_state old,
					enum srpt_command_state new)
{
	enum srpt_command_state previous;

	WARN_ON(!ioctx);
	WARN_ON(old == SRPT_STATE_DONE);
	WARN_ON(new == SRPT_STATE_NEW);

	previous = ioctx->state;
	if (previous == old)
		ioctx->state = new;

	return previous == old;
}