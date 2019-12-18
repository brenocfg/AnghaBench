#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  log_addr_mask; int /*<<< orphan*/  phys_addr; } ;
struct cec_event {TYPE_1__ state_change; int /*<<< orphan*/  event; } ;
struct TYPE_4__ {int /*<<< orphan*/  log_addr_mask; } ;
struct cec_adapter {TYPE_2__ log_addrs; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_EVENT_STATE_CHANGE ; 
 int /*<<< orphan*/  cec_queue_event (struct cec_adapter*,struct cec_event*) ; 

__attribute__((used)) static void cec_post_state_event(struct cec_adapter *adap)
{
	struct cec_event ev = {
		.event = CEC_EVENT_STATE_CHANGE,
	};

	ev.state_change.phys_addr = adap->phys_addr;
	ev.state_change.log_addr_mask = adap->log_addrs.log_addr_mask;
	cec_queue_event(adap, &ev);
}