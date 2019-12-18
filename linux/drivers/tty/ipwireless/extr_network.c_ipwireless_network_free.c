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
struct ipw_network {int shutting_down; int /*<<< orphan*/  hardware; int /*<<< orphan*/  work_go_offline; int /*<<< orphan*/  work_go_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipwireless_associate_network (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipwireless_ppp_close (struct ipw_network*) ; 
 int /*<<< orphan*/  ipwireless_stop_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipw_network*) ; 

void ipwireless_network_free(struct ipw_network *network)
{
	network->shutting_down = 1;

	ipwireless_ppp_close(network);
	flush_work(&network->work_go_online);
	flush_work(&network->work_go_offline);

	ipwireless_stop_interrupts(network->hardware);
	ipwireless_associate_network(network->hardware, NULL);

	kfree(network);
}