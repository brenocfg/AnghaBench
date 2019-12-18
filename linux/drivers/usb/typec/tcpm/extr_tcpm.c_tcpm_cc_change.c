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
struct tcpm_port {int /*<<< orphan*/  event_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  pd_event_lock; int /*<<< orphan*/  pd_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPM_CC_EVENT ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void tcpm_cc_change(struct tcpm_port *port)
{
	spin_lock(&port->pd_event_lock);
	port->pd_events |= TCPM_CC_EVENT;
	spin_unlock(&port->pd_event_lock);
	queue_work(port->wq, &port->event_work);
}