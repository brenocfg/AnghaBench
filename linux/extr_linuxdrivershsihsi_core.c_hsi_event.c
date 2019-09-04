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
struct hsi_port {int /*<<< orphan*/  n_head; } ;

/* Variables and functions */
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 

int hsi_event(struct hsi_port *port, unsigned long event)
{
	return blocking_notifier_call_chain(&port->n_head, event, NULL);
}