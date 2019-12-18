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
struct evtchn_bind_interdomain {unsigned int remote_dom; unsigned int remote_port; int /*<<< orphan*/  local_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_interdomain ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_interdomain*) ; 
 int bind_evtchn_to_irq (int /*<<< orphan*/ ) ; 

int bind_interdomain_evtchn_to_irq(unsigned int remote_domain,
				   unsigned int remote_port)
{
	struct evtchn_bind_interdomain bind_interdomain;
	int err;

	bind_interdomain.remote_dom  = remote_domain;
	bind_interdomain.remote_port = remote_port;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_bind_interdomain,
					  &bind_interdomain);

	return err ? : bind_evtchn_to_irq(bind_interdomain.local_port);
}